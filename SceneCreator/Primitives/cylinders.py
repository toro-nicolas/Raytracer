from SceneCreator.materials import *
from SceneCreator.transformations import *


class Cylinders:
    def __init__(self):
        # Default cylinder settings
        self.name = "Cylinder"
        self.content = []
        self.position = [0, 0, 0]
        self.radius = 0
        self.height = 0
        self.direction = [0, 0, 0]

        # Change values
        self.change_values = {
            "position": self.change_position,
            "radius": self.change_radius,
            "height": self.change_height,
            "direction": self.change_direction,
            "material": self.change_material,
            "transformation": self.change_transformation,
        }


    def display(self, tab=0):
        print(f"- Cylinders: ({len(self.content)})")
        for index, cylinder in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Cylinder {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{cylinder['position'][0]}, {cylinder['position'][1]}, {cylinder['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Radius: {cylinder['radius']}")
            print(f"{' ' * (tab + 8)}- Height: {cylinder['height']}")
            print(f"{' ' * (tab + 8)}- Direction: [{cylinder['direction'][0]}, {cylinder['direction'][1]}, {cylinder['direction'][2]}]")
            cylinder['materials'].display(tab + 8)
            cylinder['transformations'].display(tab + 8)


    @staticmethod
    def change_position(cylinder):
        print(f"Current position: [{cylinder['position'][0]}, {cylinder['position'][1]}, {cylinder['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                cylinder['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{cylinder['position'][0]}, {cylinder['position'][1]}, {cylinder['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_radius(cylinder):
        print(f"Current radius: {cylinder['radius']}")
        while True:
            try:
                new_radius = float(input(f"{YELLOW}Enter new radius: {RESET}"))
                cylinder['radius'] = new_radius
                print(f"{GREEN}Radius changed to: {cylinder['radius']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_height(cylinder):
        print(f"Current height: {cylinder['height']}")
        while True:
            try:
                new_height = float(input(f"{YELLOW}Enter new height: {RESET}"))
                cylinder['height'] = new_height
                print(f"{GREEN}Height changed to: {cylinder['height']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_direction(cylinder):
        print(f"Current direction: [{cylinder['direction'][0]}, {cylinder['direction'][1]}, {cylinder['direction'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x direction: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y direction: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z direction: {RESET}"))
                cylinder['direction'] = [new_x, new_y, new_z]
                print(f"{GREEN}Direction changed to: [{cylinder['direction'][0]}, {cylinder['direction'][1]}, {cylinder['direction'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_material(cylinder):
        cylinder['materials'].prompt()


    @staticmethod
    def change_transformation(cylinder):
        cylinder['transformations'].prompt()


    def add(self):
        cylinder = {"position": self.position, "radius": self.radius, "height": self.height, "direction": self.direction, "materials": Materials(), "transformations": Transformations()}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the cylinder to add:")
            print("0 - Back to add primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the cylinder")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Cylinder added.{RESET}")
                self.content.append(cylinder)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](cylinder)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_cylinder(self, cylinder):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the cylinder:")
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
                    self.change_values[key](cylinder)
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
            print("Choose a cylinder to edit:")
            print("0 - Back to edit primitive menu")
            for index, cylinder in enumerate(self.content):
                print(f"{index + 1} - Cylinder {index + 1} data: {cylinder}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    cylinder = self.content[choice]
                    print()
                    self.edit_cylinder(cylinder)
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
            print("Choose a cylinder to delete:")
            print("0 - Back to delete primitive menu")
            for index, cylinder in enumerate(self.content):
                print(f"{index + 1} - Cylinder {index + 1} data:")
                print(f"{' ' * 4}{cylinder}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Cylinder deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("    # All cylinders of the file\n")
        file.write("    cylinders = (\n")
        for cylinder in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {cylinder['position'][0]};\n")
            file.write(f"                y = {cylinder['position'][1]};\n")
            file.write(f"                z = {cylinder['position'][2]};\n")
            file.write("            };\n")
            file.write(f"            radius = {cylinder['radius']};\n")
            file.write(f"            height = {cylinder['height']};\n")
            file.write("            direction = {\n")
            file.write(f"                x = {cylinder['direction'][0]};\n")
            file.write(f"                y = {cylinder['direction'][1]};\n")
            file.write(f"                z = {cylinder['direction'][2]};\n")
            file.write("            };\n")
            cylinder['materials'].write(file)
            cylinder['transformations'].write(file)
            file.write("        },\n")
        file.write("    )\n")
