from SceneCreator.materials import *
from SceneCreator.transformations import *


class Torus:
    def __init__(self):
        # Default torus settings
        self.name = "Torus"
        self.content = []
        self.position = [0, 0, 0]
        self.minor_radius = 0
        self.major_radius = 0
        self.direction = [0, 0, 0]

        # Change values
        self.change_values = {
            "position": self.change_position,
            "minor_radius": self.change_minor_radius,
            "major_radius": self.change_major_radius,
            "direction": self.change_direction,
            "material": self.change_material,
            "transformation": self.change_transformation,
        }


    def display(self, tab=0):
        print(f"- Torus: ({len(self.content)})")
        for index, torus in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Torus {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{torus['position'][0]}, {torus['position'][1]}, {torus['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Minor radius: {torus['minor_radius']}")
            print(f"{' ' * (tab + 8)}- Major radius: {torus['major_radius']}")
            print(f"{' ' * (tab + 8)}- Direction: [{torus['direction'][0]}, {torus['direction'][1]}, {torus['direction'][2]}]")
            torus['materials'].display(tab + 8)
            torus['transformations'].display(tab + 8)


    @staticmethod
    def change_position(torus):
        print(f"Current position: [{torus['position'][0]}, {torus['position'][1]}, {torus['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                torus['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{torus['position'][0]}, {torus['position'][1]}, {torus['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_minor_radius(torus):
        print(f"Current minor radius: {torus['minor_radius']}")
        while True:
            try:
                new_minor_radius = float(input(f"{YELLOW}Enter new minor radius: {RESET}"))
                torus['minor_radius'] = new_minor_radius
                print(f"{GREEN}Minor radius changed to: {torus['minor_radius']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_major_radius(torus):
        print(f"Current major radius: {torus['major_radius']}")
        while True:
            try:
                new_major_radius = float(input(f"{YELLOW}Enter new major radius: {RESET}"))
                torus['major_radius'] = new_major_radius
                print(f"{GREEN}Major radius changed to: {torus['major_radius']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_direction(torus):
        print(f"Current direction: [{torus['direction'][0]}, {torus['direction'][1]}, {torus['direction'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x direction: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y direction: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z direction: {RESET}"))
                torus['direction'] = [new_x, new_y, new_z]
                print(f"{GREEN}Direction changed to: [{torus['direction'][0]}, {torus['direction'][1]}, {torus['direction'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_material(torus):
        torus['materials'].prompt()


    @staticmethod
    def change_transformation(torus):
        torus['transformations'].prompt()


    def add(self):
        torus = {"position": self.position, "minor_radius": self.minor_radius, "major_radius": self.major_radius, "direction": self.direction, "materials": Materials(), "transformations": Transformations()}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the torus to add:")
            print("0 - Back to add primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the torus")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Torus added.{RESET}")
                self.content.append(torus)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](torus)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_torus(self, torus):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the torus:")
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
                    self.change_values[key](torus)
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
            print("Choose a torus to edit:")
            print("0 - Back to edit primitive menu")
            for index, torus in enumerate(self.content):
                print(f"{index + 1} - Torus {index + 1} data: {torus}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    torus = self.content[choice]
                    print()
                    self.edit_torus(torus)
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
            print("Choose a torus to delete:")
            print("0 - Back to delete primitive menu")
            for index, torus in enumerate(self.content):
                print(f"{index + 1} - Torus {index + 1} data:")
                print(f"{' ' * 4}{torus}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Torus deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("    # All torus of the file\n")
        file.write("    torus = (\n")
        for torus in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {torus['position'][0]};\n")
            file.write(f"                y = {torus['position'][1]};\n")
            file.write(f"                z = {torus['position'][2]};\n")
            file.write("            };\n")
            file.write(f"            minorRadius = {torus['minor_radius']};\n")
            file.write(f"            majorRadius = {torus['major_radius']};\n")
            file.write("            direction = {\n")
            file.write(f"                x = {torus['direction'][0]};\n")
            file.write(f"                y = {torus['direction'][1]};\n")
            file.write(f"                z = {torus['direction'][2]};\n")
            file.write("            };\n")
            torus['materials'].write(file)
            torus['transformations'].write(file)
            file.write("        },\n")
        file.write("    )\n")
