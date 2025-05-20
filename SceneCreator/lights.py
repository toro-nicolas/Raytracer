from SceneCreator.Lights.directionals import *
from SceneCreator.Lights.points import *


class Lights:
    Directionals = Directionals


    class LightsTypes(Enum):
        DIRECTIONAL = 1
        POINT = 2


    class LightChoice(Enum):
        DISPLAY = 1
        AMBIENT = 2
        ADD = 3
        EDIT = 4
        DELETE = 5


    def __init__(self):
        # Lights content
        self.ambient = 50
        self.content = {
            self.LightsTypes.DIRECTIONAL: Directionals(),
            self.LightsTypes.POINT: Points(),
        }

        # Lights choices
        self.lights_settings = [
            {"id": self.LightChoice.DISPLAY, "description": "Display lights", "action": self.display},
            {"id": self.LightChoice.AMBIENT, "description": "Change ambient light", "action": self.change_ambient},
            {"id": self.LightChoice.ADD, "description": "Add a light", "action": self.add},
            {"id": self.LightChoice.EDIT, "description": "Edit a light", "action": self.edit},
            {"id": self.LightChoice.DELETE, "description": "Delete a light", "action": self.delete},
        ]


    def display(self, tab = 0):
        tab_text =  " " * tab
        print(f"{tab_text}{UNDERLINE}LIGTHS:{RESET}")
        print(f"{tab_text}- Ambient light: {self.ambient}%")
        for light_type, light in self.content.items():
            light.display(tab)


    def change_ambient(self):
        print(f"Current ambient light: {self.ambient}%")
        while True:
            try:
                new_ambient = float(input(f"{YELLOW}Enter new ambient light (0-100): {RESET}"))
                if 0 <= new_ambient <= 100:
                    self.ambient = new_ambient
                    print(f"{GREEN}Ambient light changed to: {self.ambient}%{RESET}")
                    break
                else:
                    print(f"{RED}Invalid input. Please enter a number between 0 and 100.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def add(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a light to add:")
            print("0 - Back to lights menu")
            for light_type, light in self.content.items():
                print(f"{light_type.value} - {light.name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.content):
                    print()
                    self.content[self.LightsTypes(choice)].add()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def edit(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a light to edit:")
            print("0 - Back to lights menu")
            for light_type, light in self.content.items():
                print(f"{light_type.value} - {light.name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.content):
                    print()
                    self.content[self.LightsTypes(choice)].edit()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def delete(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a light to delete:")
            print("0 - Back to lights menu")
            for light_type, light in self.content.items():
                print(f"{light_type.value} - {light.name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.content):
                    self.content[self.LightsTypes(choice)].delete()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("# The lights of the scene\n")
        file.write("lights:\n")
        file.write("{\n")
        file.write(f"    ambient = \"{self.ambient}%\";\n")
        for light in self.content.values():
            light.write(file)
        file.write("}\n")
