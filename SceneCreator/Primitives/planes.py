from SceneCreator.materials import *
from SceneCreator.transformations import *


class Planes:
    def __init__(self):
        # Default plane settings
        self.name = "Plane"
        self.content = []
        self.position = [0, 0, 0]
        self.direction = [0, 0, 0, 0, 0, 0]

        # Change values
        self.change_values = {
            "position": self.change_position,
            "direction": self.change_direction,
            "material": self.change_material,
            "transformation": self.change_transformation,
        }


    def display(self, tab=0):
        print(f"- Planes: ({len(self.content)})")
        for index, plane in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Plane {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{plane['position'][0]}, {plane['position'][1]}, {plane['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Direction: [{plane['direction'][0]}, {plane['direction'][1]}, {plane['direction'][2]}], "
                    f"[{plane['direction'][3]}, {plane['direction'][4]}, {plane['direction'][5]}]")
            plane['materials'].display(tab + 8)
            plane['transformations'].display(tab + 8)


    @staticmethod
    def change_position(plane):
        print(f"Current position: [{plane['position'][0]}, {plane['position'][1]}, {plane['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                plane['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{plane['position'][0]}, {plane['position'][1]}, {plane['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_direction(plane):
        print("Current direction:")
        print(f"- vector u = [{plane['direction'][0]}, {plane['direction'][1]}, {plane['direction'][2]}]")
        print(f"- vector v = [{plane['direction'][3]}, {plane['direction'][4]}, {plane['direction'][5]}]")
        while True:
            try:
                new_u_x = float(input(f"{YELLOW}Enter new u_x direction: {RESET}"))
                new_u_y = float(input(f"{YELLOW}Enter new u_y direction: {RESET}"))
                new_u_z = float(input(f"{YELLOW}Enter new u_z direction: {RESET}"))
                new_v_x = float(input(f"{YELLOW}Enter new v_x direction: {RESET}"))
                new_v_y = float(input(f"{YELLOW}Enter new v_y direction: {RESET}"))
                new_v_z = float(input(f"{YELLOW}Enter new v_z direction: {RESET}"))
                plane['direction'] = [new_u_x, new_u_y, new_u_z, new_v_x, new_v_y, new_v_z]
                print(f"{GREEN}Direction changed to: [{plane['direction'][0]}, {plane['direction'][1]}, {plane['direction'][2]}], "
                      f"[{plane['direction'][3]}, {plane['direction'][4]}, {plane['direction'][5]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_material(plane):
        plane['materials'].prompt()


    @staticmethod
    def change_transformation(plane):
        plane['transformations'].prompt()


    def add(self):
        plane = {"position": self.position, "direction": self.direction, "materials": Materials(), "transformations": Transformations()}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the plane to add:")
            print("0 - Back to add primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the plane")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Plane added.{RESET}")
                self.content.append(plane)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](plane)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_plane(self, plane):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the plane:")
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
                    self.change_values[key](plane)
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
            print("Choose a plane to edit:")
            print("0 - Back to edit primitive menu")
            for index, plane in enumerate(self.content):
                print(f"{index + 1} - Plane {index + 1} data: {plane}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    plane = self.content[choice]
                    print()
                    self.edit_plane(plane)
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
            print("Choose a plane to delete:")
            print("0 - Back to delete primitive menu")
            for index, plane in enumerate(self.content):
                print(f"{index + 1} - Plane {index + 1} data:")
                print(f"{' ' * 4}{plane}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Plane deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("    # All planes of the file\n")
        file.write("    planes = (\n")
        for plane in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {plane['position'][0]};\n")
            file.write(f"                y = {plane['position'][1]};\n")
            file.write(f"                z = {plane['position'][2]};\n")
            file.write("            };\n")
            file.write("            direction = {\n")
            file.write(f"                xu = {plane['direction'][0]};\n")
            file.write(f"                yu = {plane['direction'][1]};\n")
            file.write(f"                zu = {plane['direction'][2]};\n")
            file.write(f"                xv = {plane['direction'][3]};\n")
            file.write(f"                yv = {plane['direction'][4]};\n")
            file.write(f"                zv = {plane['direction'][5]};\n")
            file.write("            };\n")
            plane['materials'].write(file)
            plane['transformations'].write(file)
            file.write("        },\n")
        file.write("    )\n")
