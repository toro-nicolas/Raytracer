from SceneCreator.materials import *
from SceneCreator.transformations import *


class Triangles:
    def __init__(self):
        # Default triangle settings
        self.name = "Triangle"
        self.content = []
        self.position = [0, 0, 0]
        self.vertex1 = [0, 0, 0]
        self.vertex2 = [0, 0, 0]
        self.vertex3 = [0, 0, 0]

        # Change values
        self.change_values = {
            "position": self.change_position,
            "vertex1": self.change_vertex1,
            "vertex2": self.change_vertex2,
            "vertex3": self.change_vertex3,
            "material": self.change_material,
            "transformation": self.change_transformation,
        }


    def display(self, tab=0):
        print(f"- Triangles: ({len(self.content)})")
        for index, triangle in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Triangle {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{triangle['position'][0]}, {triangle['position'][1]}, {triangle['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Vertex1: [{triangle['vertex1'][0]}, {triangle['vertex1'][1]}, {triangle['vertex1'][2]}]")
            print(f"{' ' * (tab + 8)}- Vertex2: [{triangle['vertex2'][0]}, {triangle['vertex2'][1]}, {triangle['vertex2'][2]}]")
            print(f"{' ' * (tab + 8)}- Vertex3: [{triangle['vertex3'][0]}, {triangle['vertex3'][1]}, {triangle['vertex3'][2]}]")
            triangle['materials'].display(tab + 8)
            triangle['transformations'].display(tab + 8)


    @staticmethod
    def change_position(triangle):
        print(f"Current position: [{triangle['position'][0]}, {triangle['position'][1]}, {triangle['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                triangle['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{triangle['position'][0]}, {triangle['position'][1]}, {triangle['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_vertex1(triangle):
        print(f"Current vertex1: [{triangle['vertex1'][0]}, {triangle['vertex1'][1]}, {triangle['vertex1'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x vertex1: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y vertex1: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z vertex1: {RESET}"))
                triangle['vertex1'] = [new_x, new_y, new_z]
                print(f"{GREEN}Vertex1 changed to: [{triangle['vertex1'][0]}, {triangle['vertex1'][1]}, {triangle['vertex1'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_vertex2(triangle):
        print(f"Current vertex2: [{triangle['vertex2'][0]}, {triangle['vertex2'][1]}, {triangle['vertex2'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x vertex2: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y vertex2: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z vertex2: {RESET}"))
                triangle['vertex2'] = [new_x, new_y, new_z]
                print(f"{GREEN}Vertex2 changed to: [{triangle['vertex2'][0]}, {triangle['vertex2'][1]}, {triangle['vertex2'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_vertex3(triangle):
        print(f"Current vertex3: [{triangle['vertex3'][0]}, {triangle['vertex3'][1]}, {triangle['vertex3'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x vertex3: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y vertex3: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z vertex3: {RESET}"))
                triangle['vertex3'] = [new_x, new_y, new_z]
                print(f"{GREEN}Vertex3 changed to: [{triangle['vertex3'][0]}, {triangle['vertex3'][1]}, {triangle['vertex3'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_material(triangle):
        triangle['materials'].prompt()


    @staticmethod
    def change_transformation(triangle):
        triangle['transformations'].prompt()


    def add(self):
        triangle = {"position": self.position, "vertex1": self.vertex1, "vertex2": self.vertex2, "vertex3": self.vertex3, "materials": Materials(), "transformations": Transformations()}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the triangle to add:")
            print("0 - Back to add primitive menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the triangle")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Triangle added.{RESET}")
                self.content.append(triangle)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](triangle)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_triangle(self, triangle):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the triangle:")
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
                    self.change_values[key](triangle)
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
            print("Choose a triangle to edit:")
            print("0 - Back to edit primitive menu")
            for index, triangle in enumerate(self.content):
                print(f"{index + 1} - Triangle {index + 1} data: {triangle}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    triangle = self.content[choice]
                    print()
                    self.edit_triangle(triangle)
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
            print("Choose a triangle to delete:")
            print("0 - Back to delete primitive menu")
            for index, triangle in enumerate(self.content):
                print(f"{index + 1} - Triangle {index + 1} data:")
                print(f"{' ' * 4}{triangle}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Triangle deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("    # All triangles of the file\n")
        file.write("    triangles = (\n")
        for triangle in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {triangle['position'][0]};\n")
            file.write(f"                y = {triangle['position'][1]};\n")
            file.write(f"                z = {triangle['position'][2]};\n")
            file.write("            };\n")
            file.write("            vertex1 = {\n")
            file.write(f"                x = {triangle['vertex1'][0]};\n")
            file.write(f"                y = {triangle['vertex1'][1]};\n")
            file.write(f"                z = {triangle['vertex1'][2]};\n")
            file.write("            };\n")
            file.write("            vertex2 = {\n")
            file.write(f"                x = {triangle['vertex2'][0]};\n")
            file.write(f"                y = {triangle['vertex2'][1]};\n")
            file.write(f"                z = {triangle['vertex2'][2]};\n")
            file.write("            };\n")
            file.write("            vertex3 = {\n")
            file.write(f"                x = {triangle['vertex3'][0]};\n")
            file.write(f"                y = {triangle['vertex3'][1]};\n")
            file.write(f"                z = {triangle['vertex3'][2]};\n")
            file.write("            };\n")
            triangle['materials'].write(file)
            triangle['transformations'].write(file)
            file.write("        },\n")
        file.write("    )\n")
