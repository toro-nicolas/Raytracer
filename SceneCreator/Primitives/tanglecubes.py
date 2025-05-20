from SceneCreator.materials import *
from SceneCreator.transformations import *


class Tanglecubes:
    def __init__(self):
        # Default tanglecube settings
        self.name = "Tanglecube"
        self.content = []
        self.position = [0, 0, 0]
        self.size = 1
        self.power = 4
        self.direction = [0, 0, 0]

        # Change values
        self.change_values = {
            "position": self.change_position,
            "size": self.change_size,
            "power": self.change_power,
            "direction": self.change_direction,
            "material": self.change_material,
            "transformation": self.change_transformation,
        }


    def display(self, tab=0):
        print(f"- Tanglecubes: ({len(self.content)})")
        for index, tanglecube in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Tanglecube {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{tanglecube['position'][0]}, {tanglecube['position'][1]}, {tanglecube['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Size: {tanglecube['size']}")
            print(f"{' ' * (tab + 8)}- Power: {tanglecube['power']}")
            print(f"{' ' * (tab + 8)}- Direction: [{tanglecube['direction'][0]}, {tanglecube['direction'][1]}, {tanglecube['direction'][2]}]")
            tanglecube['materials'].display(tab + 8)
            tanglecube['transformations'].display(tab + 8)


    @staticmethod
    def change_position(tanglecube):
        print(f"Current position: [{tanglecube['position'][0]}, {tanglecube['position'][1]}, {tanglecube['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                tanglecube['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{tanglecube['position'][0]}, {tanglecube['position'][1]}, {tanglecube['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_size(tanglecube):
        print(f"Current size: {tanglecube['size']}")
        while True:
            try:
                new_size = float(input(f"{YELLOW}Enter new size: {RESET}"))
                tanglecube['size'] = new_size
                print(f"{GREEN}Size changed to: {tanglecube['size']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_power(tanglecube):
        print(f"Current power: {tanglecube['power']}")
        while True:
            try:
                new_power = int(input(f"{YELLOW}Enter new power: {RESET}"))
                tanglecube['power'] = new_power
                print(f"{GREEN}Power changed to: {tanglecube['power']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    @staticmethod
    def change_direction(tanglecube):
        print(f"Current direction: [{tanglecube['direction'][0]}, {tanglecube['direction'][1]}, {tanglecube['direction'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x direction: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y direction: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z direction: {RESET}"))
                tanglecube['direction'] = [new_x, new_y, new_z]
                print(f"{GREEN}Direction changed to: [{tanglecube['direction'][0]}, {tanglecube['direction'][1]}, {tanglecube['direction'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_material(tanglecube):
        tanglecube['materials'].prompt()


    @staticmethod
    def change_transformation(tanglecube):
        tanglecube['transformations'].prompt()


    def add(self):
        tanglecube = {"position": self.position, "size": self.size, "power": self.power, "direction": self.direction, "materials": Materials(), "transformations": Transformations()}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the tanglecube to add:")
            print("0 - Back to add primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the tanglecube")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Tanglecube added.{RESET}")
                self.content.append(tanglecube)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](tanglecube)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_tanglecube(self, tanglecube):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the tanglecube:")
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
                    self.change_values[key](tanglecube)
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
            print("Choose a tanglecube to edit:")
            print("0 - Back to edit primitive menu")
            for index, tanglecube in enumerate(self.content):
                print(f"{index + 1} - Tanglecube {index + 1} data: {tanglecube}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    tanglecube = self.content[choice]
                    print()
                    self.edit_tanglecube(tanglecube)
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
            print("Choose a tanglecube to delete:")
            print("0 - Back to delete primitive menu")
            for index, tanglecube in enumerate(self.content):
                print(f"{index + 1} - Tanglecube {index + 1} data:")
                print(f"{' ' * 4}{tanglecube}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Tanglecube deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("    # All tanglecubes of the file\n")
        file.write("    tanglecubes = (\n")
        for tanglecube in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {tanglecube['position'][0]};\n")
            file.write(f"                y = {tanglecube['position'][1]};\n")
            file.write(f"                z = {tanglecube['position'][2]};\n")
            file.write("            };\n")
            file.write(f"            size = {tanglecube['size']};\n")
            file.write(f"            power = {tanglecube['power']};\n")
            file.write("            direction = {\n")
            file.write(f"                x = {tanglecube['direction'][0]};\n")
            file.write(f"                y = {tanglecube['direction'][1]};\n")
            file.write(f"                z = {tanglecube['direction'][2]};\n")
            file.write("            };\n")
            tanglecube['materials'].write(file)
            tanglecube['transformations'].write(file)
            file.write("        },\n")
        file.write("    )\n")
