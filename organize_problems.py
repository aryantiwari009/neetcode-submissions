import os
import re
import shutil

# Root directory of your repository
REPO_ROOT = os.path.dirname(os.path.abspath(__file__))
# The specific folder where your extension currently pushes questions
TARGET_SOURCE_DIR = os.path.join(REPO_ROOT, "Data Structures & Algorithms")

def get_topic_from_readme(readme_path):
    """
    Parses the README.md file of a problem to find its topic/category tags.
    """
    if not os.path.exists(readme_path):
        return None
    
    with open(readme_path, 'r', encoding='utf-8') as f:
        content = f.read()
        
    # Pattern to match lines like "### Topics" or "Tags: Two Pointers"
    match = re.search(r'(?:Topic[s]?|Tag[s]?):\s*\*?([^\*\n]+)\*?', content, re.IGNORECASE)
    if match:
        topic = match.group(1).split(',')[0].strip()
        return topic
        
    # Fallback: Scrape for standard NeetCode categories explicitly mentioned
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
    if not os.path.exists(TARGET_SOURCE_DIR):
        print(f"Directory not found: {TARGET_SOURCE_DIR}")
        return

    # Scan everything inside 'Data Structures & Algorithms'
    for item in os.listdir(TARGET_SOURCE_DIR):
        item_path = os.path.join(TARGET_SOURCE_DIR, item)
        
        # We only want to process individual problem directories
        if os.path.isdir(item_path):
            readme_path = os.path.join(item_path, "README.md")
            
            # Identify the topic
            topic = get_topic_from_readme(readme_path)
            if not topic:
                topic = "Uncategorized"
                
            # Clean folder name (e.g., "Two Pointers" -> "Two_Pointers")
            topic_folder_name = re.sub(r'[^\w\s\-&]', '', topic).strip().replace(' ', '_')
            
            # This creates the topic folder inside 'Data Structures & Algorithms'
            # e.g., 'Data Structures & Algorithms/Arrays_&_Hashing/'
            target_dir = os.path.join(TARGET_SOURCE_DIR, topic_folder_name)
            
            # Prevent moving a topic folder into itself
            if item == topic_folder_name:
                continue
                
            os.makedirs(target_dir, exist_ok=True)
            
            dest_path = os.path.join(target_dir, item)
            print(f"Moving {item} -> {topic_folder_name}/")
            
            try:
                if os.path.exists(dest_path):
                    shutil.rmtree(dest_path) # Overwrite if it already exists
                shutil.move(item_path, target_dir)
            except Exception as e:
                print(f"Error moving {item}: {e}")

if __name__ == "__main__":
    organize_folders()
