import json
import os
import shutil

# Repository Root
ROOT = os.path.dirname(os.path.abspath(__file__))

# Folder containing newly submitted problems
UNCATEGORIZED = os.path.join(
    ROOT,
    "Data Structures & Algorithms",
    "Uncategorized"
)

# JSON file containing all NeetCode problems
DATA_FILE = os.path.join(ROOT, "problem_data.json")


def load_problem_mapping():
    """Load slug -> category mapping from problem_data.json"""

    with open(DATA_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)

    mapping = {}

    for problem in data["problems"]:

        slug = problem["slug"].strip().lower()

        category = (
            problem["category"]
            .replace(" & ", "_&_")
            .replace(" ", "_")
            .replace("/", "_")
        )

        mapping[slug] = category

    return mapping


def organize():

    if not os.path.exists(UNCATEGORIZED):
        print("Uncategorized folder not found.")
        return

    mapping = load_problem_mapping()

    moved = 0

    skipped = 0

    for folder in os.listdir(UNCATEGORIZED):

        source = os.path.join(UNCATEGORIZED, folder)

        if not os.path.isdir(source):
            continue

        slug = folder.lower().strip()

        if slug not in mapping:
            print(f"❌ {folder} -> Not found in mapping")
            skipped += 1
            continue

        topic = mapping[slug]

        destination_folder = os.path.join(
            ROOT,
            "Data Structures & Algorithms",
            topic
        )

        os.makedirs(destination_folder, exist_ok=True)

        destination = os.path.join(destination_folder, folder)

        if os.path.exists(destination):
            print(f"⚠️ {folder} already exists")
            skipped += 1
            continue

        shutil.move(source, destination)

        moved += 1

        print(f"✅ {folder} -> {topic}")

    print("\n-------------------------")
    print(f"Moved   : {moved}")
    print(f"Skipped : {skipped}")
    print("-------------------------")


if __name__ == "__main__":
    organize()
