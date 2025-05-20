from SceneCreator.Transformations.rotation import *
from SceneCreator.Transformations.translation import *


class Transformations:
    Rotation = Rotation
    Translation = Translation
    

    class TransformationsTypes(Enum):
        ROTATION = 1
        TRANSLATION = 2


    class TransformationChoice(Enum):
        DISPLAY = 1
        ADD = 2
        EDIT = 3
        DELETE = 4


    def __init__(self):
        # Transformations content
        self.can_add = [self.TransformationsTypes.ROTATION, self.TransformationsTypes.TRANSLATION]
        self.content = {}
        self.possible_content = {
            self.TransformationsTypes.ROTATION: Rotation(),
            self.TransformationsTypes.TRANSLATION: Translation(),
        }

        # Transformations choices
        self.transformations_settings = [
            {"id": self.TransformationChoice.DISPLAY, "description": "Display transformations", "action": self.display},
            {"id": self.TransformationChoice.ADD, "description": "Add a transformation", "action": self.add},
            {"id": self.TransformationChoice.EDIT, "description": "Edit a transformation", "action": self.edit},
            {"id": self.TransformationChoice.DELETE, "description": "Delete a transformation", "action": self.delete},
        ]


    def display(self, tab = 0):
        tab_text =  " " * tab
        print(f"{tab_text}- Transformations: ({len(self.content)})")
        for transformation_type, transformation in self.content.items():
            transformation.display(tab + 4)


    def add(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a transformation to add:")
            print("0 - Back to transformations menu")
            for transformation_type in self.can_add:
                print(f"{transformation_type.value} - {self.possible_content[transformation_type].name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.possible_content):
                    print()
                    new_transformation = copy.deepcopy(self.possible_content[self.TransformationsTypes(choice)])
                    if new_transformation.add():
                        self.content[self.TransformationsTypes(choice)] = new_transformation
                        self.can_add.remove(self.TransformationsTypes(choice))
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
            print("Choose a transformation to edit:")
            print("0 - Back to transformations menu")
            for transformation_index, transformation in enumerate(self.content):
                print(f"{transformation_index + 1} - {self.content[transformation].name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 0 < choice <= len(self.content):
                    print()
                    self.content[self.TransformationsTypes(choice)].edit()
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
            print("Choose a transformation to delete:")
            print("0 - Back to transformations menu")
            for transformation_index, transformation in enumerate(self.content):
                print(f"{transformation_index + 1} - {self.content[transformation].name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 0 < choice <= len(self.content):
                    del self.content[self.TransformationsTypes(choice)]
                    self.can_add.append(self.TransformationsTypes(choice))
                    print(f"{GREEN}Transformation deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("\n            # The transformations of the scene\n")
        for transformation_type, transformation in self.content.items():
            transformation.write(file)


    def prompt(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a transformation options:")
            print("0 - Back to primitive menu")
            for transformation in self.transformations_settings:
                print(f"{transformation['id'].value} - {transformation['description']}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.transformations_settings):
                    print()
                    self.transformations_settings[choice - 1]["action"]()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
