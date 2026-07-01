"""
organize_problems.py

Moves newly-synced NeetCode solutions into their correct topic folder.

Background:
    NeetCode's "GitHub Sync" feature commits every new submission directly
    to:

        <Course Folder>/<problem-slug>/submission-N.<ext>

    It does NOT create an "Uncategorized" staging folder - problems land
    straight inside the course folder (e.g. "Data Structures & Algorithms")
    next to the already-organized topic folders (e.g. "Arrays_&_Hashing").

    This script scans every course folder in the repository, finds any
    subfolder that is a *problem slug* (i.e. it matches a slug in
    problem_data.json) rather than a topic folder, and moves it into its
    topic folder, creating that folder if needed.

    If a problem folder already exists at the destination (e.g. because an
    older submission for the same problem was organized previously), the
    individual submission files are merged into the existing folder instead
    of being skipped, so no submissions are ever silently lost.
"""

import json
import os
import shutil

# Repository root (directory containing this script)
ROOT = os.path.dirname(os.path.abspath(__file__))

# JSON file containing the slug -> category mapping for every NeetCode problem
DATA_FILE = os.path.join(ROOT, "problem_data.json")

# Top-level directories that are never "course" folders and should be
# skipped entirely when scanning the repository root.
EXCLUDED_DIRS = {".git", ".github", ".vscode", "node_modules"}


def normalize_category(category):
    """Convert a raw category name (e.g. 'Arrays & Hashing') into the
    folder-name convention already used throughout this repository
    (e.g. 'Arrays_&_Hashing')."""

    name = category.strip()

    # Keep "&" but surround it with underscores: "Arrays & Hashing" -> "Arrays_&_Hashing"
    name = name.replace(" & ", "_&_")

    # "/" is not safe in folder names on some filesystems/tools - normalize
    # it the same way, e.g. "Heap / Priority Queue" -> "Heap_Priority_Queue"
    name = name.replace(" / ", "_").replace("/", "_")

    # Replace any remaining whitespace with underscores
    name = "_".join(name.split())

    # Collapse any accidental repeated underscores from the steps above
    while "__" in name:
        name = name.replace("__", "_")

    return name


def load_problem_mapping():
    """Load slug -> normalized topic-folder-name mapping from problem_data.json"""

    with open(DATA_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)

    mapping = {}

    for problem in data["problems"]:
        slug = problem["slug"].strip().lower()
        mapping[slug] = normalize_category(problem["category"])

    return mapping


def get_course_dirs():
    """Return every top-level folder in the repository that can contain
    NeetCode submissions (everything except VCS/config folders)."""

    course_dirs = []

    for entry in os.listdir(ROOT):
        full_path = os.path.join(ROOT, entry)

        if entry in EXCLUDED_DIRS:
            continue

        if not os.path.isdir(full_path):
            continue

        course_dirs.append(full_path)

    return course_dirs


def merge_or_move(source, destination_folder, folder_name):
    """Move `source` into `destination_folder`. If a folder with the same
    name already exists at the destination, merge the contents (moving
    each file individually) instead of skipping the whole folder, so no
    submissions are lost."""

    os.makedirs(destination_folder, exist_ok=True)

    destination = os.path.join(destination_folder, folder_name)

    if not os.path.exists(destination):
        shutil.move(source, destination)
        return "moved"

    # Destination already exists: merge file-by-file instead of skipping.
    merged_any = False
    leftover = False

    for item in os.listdir(source):
        src_item = os.path.join(source, item)
        dst_item = os.path.join(destination, item)

        if os.path.exists(dst_item):
            # Same submission file already present at the destination -
            # leave it in place rather than overwriting anything.
            leftover = True
            continue

        shutil.move(src_item, dst_item)
        merged_any = True

    # Remove the now-empty source folder. If some files could not be
    # merged (name collision), leave the folder with the leftovers so
    # nothing is silently deleted.
    if not leftover and not os.listdir(source):
        os.rmdir(source)

    if merged_any and leftover:
        return "merged_with_leftovers"
    if merged_any:
        return "merged"
    return "already_up_to_date"


def organize():
    mapping = load_problem_mapping()

    moved = 0
    merged = 0
    skipped = 0

    for course_dir in get_course_dirs():
        for entry in sorted(os.listdir(course_dir)):
            source = os.path.join(course_dir, entry)

            if not os.path.isdir(source):
                continue

            slug = entry.strip().lower()

            if slug not in mapping:
                # Not a recognized problem slug - this is either an
                # already-organized topic folder (e.g. "Arrays_&_Hashing")
                # or something unrelated. Leave it untouched.
                continue

            topic = mapping[slug]

            # Folder is already sitting directly inside its correct topic
            # folder (shouldn't normally happen, but guard against it).
            if os.path.basename(course_dir) == topic:
                continue

            destination_folder = os.path.join(course_dir, topic)

            result = merge_or_move(source, destination_folder, entry)

            if result == "moved":
                moved += 1
                print(f"✅ {entry} -> {topic}")
            elif result in ("merged", "merged_with_leftovers"):
                merged += 1
                print(f"🔀 {entry} -> {topic} (merged submissions)")
            else:
                skipped += 1
                print(f"⚠️ {entry} already up to date in {topic}")

    print("\n-------------------------")
    print(f"Moved   : {moved}")
    print(f"Merged  : {merged}")
    print(f"Skipped : {skipped}")
    print("-------------------------")


if __name__ == "__main__":
    organize()
