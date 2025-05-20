from SceneCreator.materials import *
from SceneCreator.transformations import *


class Spheres:
    def __init__(self):
        # Default sphere settings
        self.name = "Sphere"
        self.content = []
        self.position = [0, 0, 0]
        self.radius = 0

        # Change values
        self.change_values = {
            "position": self.change_position,
            "radius": self.change_radius,
            "material": self.change_material,
            "transformation": self.change_transformation,
        }


    def display(self, tab=0):
        print(f"- Spheres: ({len(self.content)})")
        for index, sphere in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Sphere {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{sphere['position'][0]}, {sphere['position'][1]}, {sphere['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Radius: {sphere['radius']}")
            sphere['materials'].display(tab + 8)
            sphere['transformations'].display(tab + 8)


    @staticmethod
    def change_position(sphere):
        print(f"Current position: [{sphere['position'][0]}, {sphere['position'][1]}, {sphere['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                sphere['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{sphere['position'][0]}, {sphere['position'][1]}, {sphere['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_radius(sphere):
        print(f"Current radius: {sphere['radius']}")
        while True:
            try:
                new_radius = float(input(f"{YELLOW}Enter new radius: {RESET}"))
                sphere['radius'] = new_radius
                print(f"{GREEN}Radius changed to: {sphere['radius']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_material(sphere):
        sphere['materials'].prompt()


    @staticmethod
    def change_transformation(sphere):
        sphere['transformations'].prompt()


    def add(self):
        sphere = {"position": self.position, "radius": self.radius, "materials": Materials(), "transformations": Transformations()}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the sphere to add:")
            print("0 - Back to add primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the sphere")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Sphere added.{RESET}")
                self.content.append(sphere)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](sphere)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_sphere(self, sphere):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the sphere:")
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
                    self.change_values[key](sphere)
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
            print("Choose a sphere to edit:")
            print("0 - Back to edit primitive menu")
            for index, sphere in enumerate(self.content):
                print(f"{index + 1} - Sphere {index + 1} data: {sphere}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    sphere = self.content[choice]
                    print()
                    self.edit_sphere(sphere)
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
            print("Choose a sphere to delete:")
            print("0 - Back to delete primitive menu")
            for index, sphere in enumerate(self.content):
                print(f"{index + 1} - Sphere {index + 1} data:")
                print(f"{' ' * 4}{sphere}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Sphere deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("    # All spheres of the file\n")
        file.write("    spheres = (\n")
        for sphere in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {sphere['position'][0]};\n")
            file.write(f"                y = {sphere['position'][1]};\n")
            file.write(f"                z = {sphere['position'][2]};\n")
            file.write("            };\n")
            file.write(f"            radius = {sphere['radius']};\n")
            sphere['materials'].write(file)
            sphere['transformations'].write(file)
            file.write("        },\n")
        file.write("    )\n")
