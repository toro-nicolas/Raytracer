from SceneCreator.utils import *


class Points:
    def __init__(self):
        # Default point settings
        self.name = "Point"
        self.content = []
        self.position = [0, 0, 0]
        self.intensity = 100
        self.color = [255, 255, 255]

        # Change values
        self.change_values = {
            "position": self.change_position,
            "intensity": self.change_intensity,
            "color": self.change_color,
        }


    def display(self, tab=0):
        print(f"- Points: ({len(self.content)})")
        for index, point in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Point {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{point['position'][0]}, {point['position'][1]}, {point['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Intensity: {point['intensity']}")
            print(f"{' ' * (tab + 8)}- Color: [{point['color'][0]}, {point['color'][1]}, {point['color'][2]}]")


    @staticmethod
    def change_position(point):
        print(f"Current position: [{point['position'][0]}, {point['position'][1]}, {point['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                point['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{point['position'][0]}, {point['position'][1]}, {point['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_intensity(point):
        print(f"Current intensity: {point['intensity']}")
        while True:
            try:
                new_intensity = float(input(f"{YELLOW}Enter new intensity: {RESET}"))
                point['intensity'] = new_intensity
                print(f"{GREEN}Intensity changed to: {point['intensity']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_color(point):
        print(f"Current color: [{point['color'][0]}, {point['color'][1]}, {point['color'][2]}]")
        while True:
            try:
                new_r = int(input(f"{YELLOW}Enter new red color value (0-255): {RESET}"))
                new_g = int(input(f"{YELLOW}Enter new green color value (0-255): {RESET}"))
                new_b = int(input(f"{YELLOW}Enter new blue color value (0-255): {RESET}"))
                if 0 <= new_r <= 255 and 0 <= new_g <= 255 and 0 <= new_b <= 255:
                    point['color'] = [new_r, new_g, new_b]
                    print(f"{GREEN}Color changed to: [{point['color'][0]}, {point['color'][1]}, {point['color'][2]}]{RESET}")
                    break
                else:
                    print(f"{RED}Invalid input. Please enter values between 0 and 255.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    def add(self):
        point = {"position": self.position, "intensity": self.intensity, "color": self.color}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the point to add:")
            print("0 - Back to add light menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the point")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Point added.{RESET}")
                self.content.append(point)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](point)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_point(self, point):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the point:")
            print("0 - Back to edit light menu")
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
                    self.change_values[key](point)
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
            print("Choose a point to edit:")
            print("0 - Back to edit light menu")
            for index, point in enumerate(self.content):
                print(f"{index + 1} - Point {index + 1} data: {point}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    point = self.content[choice]
                    print()
                    self.edit_point(point)
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
            print("Choose a point to delete:")
            print("0 - Back to delete light menu")
            for index, point in enumerate(self.content):
                print(f"{index + 1} - Point {index + 1} data:")
                print(f"{' ' * 4}{point}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Point deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("\n    # All points of the file\n")
        file.write("    points = (\n")
        for point in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {point['position'][0]};\n")
            file.write(f"                y = {point['position'][1]};\n")
            file.write(f"                z = {point['position'][2]};\n")
            file.write("            },\n")
            file.write(f"            intensity = \"{point['intensity']}%\";\n")
            file.write("            color = {\n")
            file.write(f"                r = {point['color'][0]};\n")
            file.write(f"                g = {point['color'][1]};\n")
            file.write(f"                b = {point['color'][2]};\n")
            file.write("            },\n")
            file.write("        },\n")
        file.write("    )\n")
