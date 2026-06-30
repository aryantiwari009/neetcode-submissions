import os
import re
import shutil

REPO_ROOT = os.path.dirname(os.path.abspath(__file__))

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
        
    categories = [
        "Arrays & Hashing", "Two Pointers", "Sliding Window", "Stack", 
        "Binary Search", "Linked List", "Trees", "Tries", "Heap", 
        "Backtracking", "Graphs", "Advanced Graphs", "Dynamic Programming", 
        "Greedy", "Intervals", "Math & Geometry", "Bit Manipulation", "String"
    ]
    for cat in categories:
        if re.search(rf'\b{cat}\b', content, re.IGNORECASE):
            return cat
    return None

def organize_folders():
    # Dynamically find the directory containing your problems
    target_dir_name = "Data Structures & Algorithms"
    source_dir = os.path.join(REPO_ROOT, target_dir_name)
    
    if not os.path.exists(source_dir):
        # Fallback in case of encoding mismatches in the environment
        for item in os.listdir(REPO_ROOT):
            if "Data Structures" in item and os.path.isdir(os.path.join(REPO_ROOT, item)):
                source_dir = os.path.join(REPO_ROOT, item)
                break
                
    if not os.path.exists(source_dir):
        print("Target directory not found.")
        return

    for item in os.listdir(source_dir):
        item_path = os.path.join(source_dir, item)
        
        if os.path.isdir(item_path):
            # Skip folders that are already clean topic folders
            if item in ["Arrays_&_Hashing", "Two_Pointers", "Sliding_Window", "Stack", "Binary_Search", "Linked_List", "Trees", "Tries", "Heap", "Backtracking", "Graphs", "Advanced_Graphs", "Dynamic_Programming", "Greedy", "Intervals", "Math_&_Geometry", "Bit_Manipulation", "String", "Uncategorized"]:
                continue
                
            readme_path = os.path.join(item_path, "README.md")
            topic = get_topic_from_readme(readme_path) or "Uncategorized"
            
            topic_folder_name = re.sub(r'[^\w\s\-&]', '', topic).strip().replace(' ', '_')
            target_topic_dir = os.path.join(source_dir, topic_folder_name)
            
            os.makedirs(target_topic_dir, exist_ok=True)
            dest_path = os.path.join(target_topic_dir, item)
            
            try:
                if os.path.exists(dest_path):
                    shutil.rmtree(dest_path)
                shutil.move(item_path, target_topic_dir)
                print(f"Successfully moved {item} to {topic_folder_name}")
            except Exception as e:
                print(f"Failed to move {item}: {e}")

if __name__ == "__main__":
    organize_folders()
