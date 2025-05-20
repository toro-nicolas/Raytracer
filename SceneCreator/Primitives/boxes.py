from SceneCreator.materials import *
from SceneCreator.transformations import *


class Boxes:
    def __init__(self):
        # Default box settings
        self.name = "Box"
        self.content = []
        self.position = [0, 0, 0]
        self.size = [0, 0, 0]

        # Change values
        self.change_values = {
            "position": self.change_position,
            "size": self.change_size,
            "material": self.change_material,
            "transformation": self.change_transformation,
        }


    def display(self, tab=0):
        print(f"- Boxes: ({len(self.content)})")
        for index, box in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Box {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{box['position'][0]}, {box['position'][1]}, {box['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Size: [{box['size'][0]}, {box['size'][1]}, {box['size'][2]}]")
            box['materials'].display(tab + 8)
            box['transformations'].display(tab + 8)


    @staticmethod
    def change_position(box):
        print(f"Current position: [{box['position'][0]}, {box['position'][1]}, {box['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                box['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{box['position'][0]}, {box['position'][1]}, {box['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_size(box):
        print(f"Current size: [{box['size'][0]}, {box['size'][1]}, {box['size'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x size: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y size: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z size: {RESET}"))
                box['size'] = [new_x, new_y, new_z]
                print(f"{GREEN}Size changed to: [{box['size'][0]}, {box['size'][1]}, {box['size'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_material(box):
        box['materials'].prompt()


    @staticmethod
    def change_transformation(box):
        box['transformations'].prompt()


    def add(self):
        box = {"position": self.position, "size": self.size, "materials": Materials(), "transformations": Transformations()}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the box to add:")
            print("0 - Back to add primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the box")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Box added.{RESET}")
                self.content.append(box)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](box)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_box(self, box):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the box:")
            print("0 - Back to edit primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](box)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a box to edit:")
            print("0 - Back to edit primitive menu")
            for index, box in enumerate(self.content):
                print(f"{index + 1} - Box {index + 1} data: {box}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    box = self.content[choice]
                    print()
                    self.edit_box(box)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def delete(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a box to delete:")
            print("0 - Back to delete primitive menu")
            for index, box in enumerate(self.content):
                print(f"{index + 1} - Box {index + 1} data:")
                print(f"{' ' * 4}{box}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Box deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("    # All boxes of the file\n")
        file.write("    boxs = (\n") #TODO change to boxes
        for box in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {box['position'][0]};\n")
            file.write(f"                y = {box['position'][1]};\n")
            file.write(f"                z = {box['position'][2]};\n")
            file.write("            };\n")
            file.write("            size = {\n")
            file.write(f"                u = {box['size'][0]};\n")
            file.write(f"                u = {box['size'][1]};\n")
            file.write(f"                u = {box['size'][2]};\n")
            file.write("            };\n")
            box['materials'].write(file)
            box['transformations'].write(file)
            file.write("        },\n")
        file.write("    )\n")
