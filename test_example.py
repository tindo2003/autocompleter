import re
# from playwright.sync_api import Page, expect


# def test_has_title(page: Page):
#     page.goto("https://playwright.dev/")

#     # Expect a title "to contain" a substring.
#     expect(page).to_have_title(re.compile("Playwright"))


# def test_get_started_link(page: Page):
#     page.goto("https://playwright.dev/")

#     # Click the get started link.
#     page.get_by_role("link", name="Get started").click()

#     # Expects page to have a heading with the name of Installation.
#     expect(page.get_by_role("heading", name="Installation")).to_be_visible()

class Node:
    def __init__(self, val: int):
        self.next = None
        self.val = val 

class Tree:
    @staticmethod
    def init_tree():
        new_node = Node(10)
        return new_node
    
def main():
    res = Tree.init_tree() 
    print(res.val)
    
if __name__ == "__main__":
    main()