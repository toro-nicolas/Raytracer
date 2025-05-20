from SceneCreator.Materials.color import *
from SceneCreator.Materials.diffuseLight import *
from SceneCreator.Materials.reflection import *
from SceneCreator.Materials.refraction import *


class Materials:
    Color = Color


    class MaterialsTypes(Enum):
        COLOR = 1
        DIFFUSELIGHT = 2
        REFLECTION = 3
        REFRACTION = 4


    class MaterialChoice(Enum):
        DISPLAY = 1
        ADD = 2
        EDIT = 3
        DELETE = 4


    def __init__(self):
        # Materials content
        self.can_add = [self.MaterialsTypes.COLOR, self.MaterialsTypes.DIFFUSELIGHT, self.MaterialsTypes.REFLECTION, self.MaterialsTypes.REFRACTION]
        self.content = {}
        self.possible_content = {
            self.MaterialsTypes.COLOR: Color(),
            self.MaterialsTypes.DIFFUSELIGHT: DiffuseLight(),
            self.MaterialsTypes.REFLECTION: Reflection(),
            self.MaterialsTypes.REFRACTION: Refraction(),
        }

        # Materials choices
        self.materials_settings = [
            {"id": self.MaterialChoice.DISPLAY, "description": "Display materials", "action": self.display},
            {"id": self.MaterialChoice.ADD, "description": "Add a material", "action": self.add},
            {"id": self.MaterialChoice.EDIT, "description": "Edit a material", "action": self.edit},
            {"id": self.MaterialChoice.DELETE, "description": "Delete a material", "action": self.delete},
        ]


    def display(self, tab = 0):
        tab_text =  " " * tab
        print(f"{tab_text}- Materials: ({len(self.content)})")
        for material_type, material in self.content.items():
            material.display(tab + 4)


    def add(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a material to add:")
            print("0 - Back to materials menu")
            for material_type in self.can_add:
                print(f"{material_type.value} - {self.possible_content[material_type].name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.possible_content):
                    print()
                    new_material = copy.deepcopy(self.possible_content[self.MaterialsTypes(choice)])
                    if new_material.add():
                        self.content[self.MaterialsTypes(choice)] = new_material
                        self.can_add.remove(self.MaterialsTypes(choice))
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
            print("Choose a material to edit:")
            print("0 - Back to materials menu")
            for material_index, material in enumerate(self.content):
                print(f"{material_index + 1} - {self.content[material].name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 0 < choice <= len(self.content):
                    print()
                    self.content[self.MaterialsTypes(choice)].edit()
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
            print("Choose a material to delete:")
            print("0 - Back to materials menu")
            for material_index, material in enumerate(self.content):
                print(f"{material_index + 1} - {self.content[material].name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 0 < choice <= len(self.content):
                    del self.content[self.MaterialsTypes(choice)]
                    self.can_add.append(self.MaterialsTypes(choice))
                    print(f"{GREEN}Material deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("\n            # The materials of the scene\n")
        for material_type, material in self.content.items():
            material.write(file)


    def prompt(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a material options:")
            print("0 - Back to primitive menu")
            for material in self.materials_settings:
                print(f"{material['id'].value} - {material['description']}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.materials_settings):
                    print()
                    self.materials_settings[choice - 1]["action"]()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
