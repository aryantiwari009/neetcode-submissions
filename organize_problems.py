import os
import re
import shutil
import urllib.request
import json

REPO_ROOT = os.path.dirname(os.path.abspath(__file__))

def fetch_neetcode_mapping():
    """Dynamically fetches the problem-to-category mapping from NeetCode's public data structure."""
    url = "https://raw.githubusercontent.com/neetcode-gh/neetcode.io/main/src/data/neetcode250.json"
    try:
        with urllib.request.urlopen(url) as response:
            data = json.loads(response.read().decode())
            
        mapping = {}
        # Traverse the NeetCode 250 JSON structure
        for chapter in data:
            category_name = chapter.get("name", "").strip()
            # Clean up category names to look nice as folders (e.g., "Arrays & Hashing")
            if "Arrays" in category_name and "Hashing" in category_name:
                # Standardize to what you prefer or leave separate based on sheet split
                pass 
                
            for problem in chapter.get("problems", []):
                # The folder name matches the link identifier slug (e.g., 'is-anagram')
                link = problem.get("link", "")
                slug_match = re.search(r'problems/([^/]+)', link)
                if slug_match:
                    problem_slug = slug_match.group(1).lower().strip()
                    mapping[problem_slug] = category_name
                    
        return mapping
    except Exception as e:
        print(f"Failed to fetch dynamic NeetCode roadmap data: {e}")
        return {}

def get_topic_from_readme(readme_path):
    if not os.path.exists(readme_path):
        return None
    try:
        with open(readme_path, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception:
        return None
        
    match = re.search(r'(?:Topic[s]?|Tag[s]?):\s*\*?([^\*\n]+)\*?', content, re.IGNORECASE)
    if match:
        return match.group(1).split(',')[0].strip()
    return None

def organize_folders():
    target_dir_name = "Data Structures & Algorithms"
    source_dir = os.path.join(REPO_ROOT, target_dir_name)
    
    if not os.path.exists(source_dir):
        for item in os.listdir(REPO_ROOT):
            if "Data Structures" in item and os.path.isdir(os.path.join(REPO_ROOT, item)):
                source_dir = os.path.join(REPO_ROOT, item)
                break
                
    if not os.path.exists(source_dir):
        print("Target directory not found.")
        return

    # Fetch the live list from NeetCode
    print("Fetching live NeetCode 250 data tracking mapping...")
    problem_map = fetch_neetcode_mapping()

    # Scan both the root directory and the Uncategorized folder
    directories_to_scan = [source_dir]
    uncategorized_dir = os.path.join(source_dir, "Uncategorized")
    if os.path.exists(uncategorized_dir):
        directories_to_scan.append(uncategorized_dir)

    for scan_dir in directories_to_scan:
        for item in os.listdir(scan_dir):
            item_path = os.path.join(scan_dir, item)
            
            if os.path.isdir(item_path):
                # Keep target operational category folders safe
                if item in ["Arrays", "Hashing", "Two_Pointers", "Sliding_Window", "Stack", "Binary_Search", "Linked_List", "Trees", "Tries", "Heap", "Backtracking", "Graphs", "Advanced_Graphs", "Dynamic_Programming", "Greedy", "Intervals", "Math_&_Geometry", "Bit_Manipulation", "String", "Uncategorized"]:
                    continue
                    
                # 1. Match dynamically against the retrieved live NeetCode index map
                topic = problem_map.get(item.lower().strip())
                
                # 2. Fallback to local README metadata parsing if live data doesn't hit
                if not topic:
                    readme_path = os.path.join(item_path, "README.md")
                    topic = get_topic_from_readme(readme_path) or "Uncategorized"
                
                if scan_dir == uncategorized_dir and topic == "Uncategorized":
                    continue
                
                # Sanitize the folder name to use underscores instead of spaces
                topic_folder_name = re.sub(r'[^\w\s\-&]', '', topic).strip().replace(' ', '_')
                target_topic_dir = os.path.join(source_dir, topic_folder_name)
                
                os.makedirs(target_topic_dir, exist_ok=True)
                dest_path = os.path.join(target_topic_dir, item)
                
                try:
                    if os.path.exists(dest_path):
                        shutil.rmtree(dest_path)
                    shutil.move(item_path, target_topic_dir)
                    print(f"Dynamically moved {item} to {topic_folder_name}")
                except Exception as e:
                    print(f"Failed to move {item}: {e}")

if __name__ == "__main__":
    organize_folders()
