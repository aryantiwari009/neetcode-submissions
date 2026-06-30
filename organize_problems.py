import json
import os
import shutil

ROOT = os.path.dirname(os.path.abspath(__file__))

UNCATEGORIZED = os.path.join(
    ROOT,
    "Data Structures & Algorithms",
    "Uncategorized"
)

MAPPING_FILE = os.path.join(ROOT, "problem_mapping.json")


def load_mapping():
    with open(MAPPING_FILE, "r", encoding="utf-8") as f:
        return json.load(f)


def organize():

    mapping = load_mapping()

    if not os.path.exists(UNCATEGORIZED):
        print("Uncategorized folder not found.")
        return

    for folder in os.listdir(UNCATEGORIZED):

        source = os.path.join(UNCATEGORIZED, folder)

        if not os.path.isdir(source):
            continue

        topic = mapping.get(folder.lower())

        if topic is None:
            print(f"{folder} -> Uncategorized")
            continue

        destination_folder = os.path.join(
            ROOT,
            "Data Structures & Algorithms",
            topic
        )

        os.makedirs(destination_folder, exist_ok=True)

        destination = os.path.join(destination_folder, folder)

        if os.path.exists(destination):
            print(f"{folder} already exists")
            continue

        shutil.move(source, destination)

        print(f"Moved {folder} -> {topic}")


if __name__ == "__main__":
    organize()
