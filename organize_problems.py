import os
import re
import shutil
import urllib.request
import json

# Since the script is running inside "Uncategorized", REPO_ROOT is the Uncategorized folder!
CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))

def fetch_neetcode_mapping():
    url = "https://raw.githubusercontent.com/neetcode-gh/neetcode.io/main/src/data/neetcode250.json"
    try:
        req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla'})
        with urllib.request.urlopen(req) as response:
            data = json.loads(response.read().decode())
        
        mapping = {}
        for chapter in data:
            category_name = chapter.get("name", "").strip()
            for problem in chapter.get("problems", []):
                link = problem.get("link", "")
                slug_match = re.search(r'problems/([^/]+)', link)
                if slug_match:
                    mapping[slug_match.group(1).lower().strip()] = category_name
        return mapping
    except Exception as e:
        print(f"Failed to fetch NeetCode data: {e}")
        return {}

def organize_folders():
    # The parent directory is "Data Structures & Algorithms"
    parent_dir = os.path.dirname(CURRENT_DIR)
    
    print("Fetching live NeetCode 250 data tracking mapping...")
    problem_map = fetch_neetcode_mapping()

    protected_folders = [
        "Arrays", "Hashing", "Two_Pointers", "Sliding_Window", "Stack", 
        "Binary_Search", "Linked_List", "Trees", "Tries", "Heap", 
        "Backtracking", "Graphs", "Advanced_Graphs", "Dynamic_Programming", 
        "Greedy", "Intervals", "Math_&_Geometry", "Bit_Manipulation", "Uncategorized"
    ]

    # Scan everything inside the current "Uncategorized" folder
    for item in os.listdir(CURRENT_DIR):
        item_path = os.path.join(CURRENT_DIR, item)
        
        if os.path.isdir(item_path):
            if item in protected_folders:
                continue
                
            # Get the category from NeetCode mapping
            topic = problem_map.get(item.lower().strip()) or "Uncategorized"
            
            if topic == "Uncategorized":
                continue
                
            # Clean up the folder name (e.g., "Two Pointers" -> "Two_Pointers")
            topic_folder_name = re.sub(r'[^\w\s\-&]', '', topic).strip().replace(' ', '_')
            
            # The destination path should be up one level, inside the proper category folder
            target_topic_dir = os.path.join(parent_dir, topic_folder_name)
            os.makedirs(target_topic_dir, exist_ok=True)
            
            dest_path = os.path.join(target_topic_dir, item)
            
            try:
                if os.path.exists(dest_path):
                    shutil.rmtree(dest_path)
                shutil.move(item_path, target_topic_dir)
                print(f"Successfully moved {item} out to {topic_folder_name}")
            except Exception as e:
                print(f"Failed to move {item}: {e}")

if __name__ == "__main__":
    organize_folders()
