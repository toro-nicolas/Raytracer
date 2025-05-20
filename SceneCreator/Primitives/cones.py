from SceneCreator.materials import *
from SceneCreator.transformations import *


class Cones:
    def __init__(self):
        # Default cone settings
        self.name = "Cone"
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
        print(f"- Cones: ({len(self.content)})")
        for index, cone in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Cone {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{cone['position'][0]}, {cone['position'][1]}, {cone['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Radius: {cone['radius']}")
            print(f"{' ' * (tab + 8)}- Height: {cone['height']}")
            print(f"{' ' * (tab + 8)}- Direction: [{cone['direction'][0]}, {cone['direction'][1]}, {cone['direction'][2]}]")
            cone['materials'].display(tab + 8)
            cone['transformations'].display(tab + 8)


    @staticmethod
    def change_position(cone):
        print(f"Current position: [{cone['position'][0]}, {cone['position'][1]}, {cone['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                cone['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{cone['position'][0]}, {cone['position'][1]}, {cone['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_radius(cone):
        print(f"Current radius: {cone['radius']}")
        while True:
            try:
                new_radius = float(input(f"{YELLOW}Enter new radius: {RESET}"))
                cone['radius'] = new_radius
                print(f"{GREEN}Radius changed to: {cone['radius']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_height(cone):
        print(f"Current height: {cone['height']}")
        while True:
            try:
                new_height = float(input(f"{YELLOW}Enter new height: {RESET}"))
                cone['height'] = new_height
                print(f"{GREEN}Height changed to: {cone['height']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_direction(cone):
        print(f"Current direction: [{cone['direction'][0]}, {cone['direction'][1]}, {cone['direction'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x direction: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y direction: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z direction: {RESET}"))
                cone['direction'] = [new_x, new_y, new_z]
                print(f"{GREEN}Direction changed to: [{cone['direction'][0]}, {cone['direction'][1]}, {cone['direction'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_material(cone):
        cone['materials'].prompt()


    @staticmethod
    def change_transformation(cone):
        cone['transformations'].prompt()


    def add(self):
        cone = {"position": self.position, "radius": self.radius, "height": self.height, "direction": self.direction, "materials": Materials(), "transformations": Transformations()}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the cone to add:")
            print("0 - Back to add primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the cone")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Cone added.{RESET}")
                self.content.append(cone)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](cone)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_cone(self, cone):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the cone:")
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
                    self.change_values[key](cone)
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
            print("Choose a cone to edit:")
            print("0 - Back to edit primitive menu")
            for index, cone in enumerate(self.content):
                print(f"{index + 1} - Cone {index + 1} data: {cone}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    cone = self.content[choice]
                    print()
                    self.edit_cone(cone)
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
            print("Choose a cone to delete:")
            print("0 - Back to delete primitive menu")
            for index, cone in enumerate(self.content):
                print(f"{index + 1} - Cone {index + 1} data:")
                print(f"{' ' * 4}{cone}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Cone deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("    # All cones of the file\n")
        file.write("    cones = (\n")
        for cone in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {cone['position'][0]};\n")
            file.write(f"                y = {cone['position'][1]};\n")
            file.write(f"                z = {cone['position'][2]};\n")
            file.write("            };\n")
            file.write(f"            radius = {cone['radius']};\n")
            file.write(f"            height = {cone['height']};\n")
            file.write("            direction = {\n")
            file.write(f"                x = {cone['direction'][0]};\n")
            file.write(f"                y = {cone['direction'][1]};\n")
            file.write(f"                z = {cone['direction'][2]};\n")
            file.write("            };\n")
            cone['materials'].write(file)
            cone['transformations'].write(file)
            file.write("        },\n")
        file.write("    )\n")
