from SceneCreator.utils import *


class Directionals:
    def __init__(self):
        # Default directional settings
        self.name = "Directional"
        self.content = []
        self.position = [0, 0, 0]
        self.intensity = 100
        self.color = [255, 255, 255]
        self.direction = [0, 0, 0]

        # Change values
        self.change_values = {
            "position": self.change_position,
            "intensity": self.change_intensity,
            "color": self.change_color,
            "direction": self.change_direction,
        }


    def display(self, tab=0):
        print(f"- Directionals: ({len(self.content)})")
        for index, directional in enumerate(self.content):
            print(f"{' ' * (tab + 4)}- Directional {index + 1} data:")
            print(f"{' ' * (tab + 8)}- Position: [{directional['position'][0]}, {directional['position'][1]}, {directional['position'][2]}]")
            print(f"{' ' * (tab + 8)}- Intensity: {directional['intensity']}")
            print(f"{' ' * (tab + 8)}- Color: [{directional['color'][0]}, {directional['color'][1]}, {directional['color'][2]}]")
            print(f"{' ' * (tab + 8)}- Direction: [{directional['direction'][0]}, {directional['direction'][1]}, {directional['direction'][2]}]")


    @staticmethod
    def change_position(directional):
        print(f"Current position: [{directional['position'][0]}, {directional['position'][1]}, {directional['position'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                directional['position'] = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{directional['position'][0]}, {directional['position'][1]}, {directional['position'][2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_intensity(directional):
        print(f"Current intensity: {directional['intensity']}")
        while True:
            try:
                new_intensity = float(input(f"{YELLOW}Enter new intensity: {RESET}"))
                directional['intensity'] = new_intensity
                print(f"{GREEN}Intensity changed to: {directional['intensity']}{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    @staticmethod
    def change_color(directional):
        print(f"Current color: [{directional['color'][0]}, {directional['color'][1]}, {directional['color'][2]}]")
        while True:
            try:
                new_r = int(input(f"{YELLOW}Enter new red color value (0-255): {RESET}"))
                new_g = int(input(f"{YELLOW}Enter new green color value (0-255): {RESET}"))
                new_b = int(input(f"{YELLOW}Enter new blue color value (0-255): {RESET}"))
                if 0 <= new_r <= 255 and 0 <= new_g <= 255 and 0 <= new_b <= 255:
                    directional['color'] = [new_r, new_g, new_b]
                    print(f"{GREEN}Color changed to: [{directional['color'][0]}, {directional['color'][1]}, {directional['color'][2]}]{RESET}")
                    break
                else:
                    print(f"{RED}Invalid input. Please enter values between 0 and 255.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    @staticmethod
    def change_direction(directional):
        print(f"Current direction: [{directional['direction'][0]}, {directional['direction'][1]}, {directional['direction'][2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x direction: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y direction: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z direction: {RESET}"))
                directional['direction'] = [new_x, new_y, new_z]
                print(f"{GREEN}Direction changed to: [{directional['direction'][0]}, {directional['direction'][1]}, {directional['direction'][2]}]")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    def add(self):
        directional = {"position": self.position, "intensity": self.intensity, "color": self.color, "direction": self.direction}
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the directional to add:")
            print("0 - Back to add light menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the directional")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Directional added.{RESET}")
                self.content.append(directional)
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key](directional)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit_directional(self, directional):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Edit the directional:")
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
                    self.change_values[key](directional)
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
            print("Choose a directional to edit:")
            print("0 - Back to edit light menu")
            for index, directional in enumerate(self.content):
                print(f"{index + 1} - Directional {index + 1} data: {directional}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    directional = self.content[choice]
                    print()
                    self.edit_directional(directional)
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
            print("Choose a directional to delete:")
            print("0 - Back to delete light menu")
            for index, directional in enumerate(self.content):
                print(f"{index + 1} - Directional {index + 1} data:")
                print(f"{' ' * 4}{directional}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.content):
                    del self.content[choice]
                    print(f"{GREEN}Directional deleted.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("\n    # All directionals of the file\n")
        file.write("    directionals = (\n")
        for directional in self.content:
            file.write("        {\n")
            file.write("            position = {\n")
            file.write(f"                x = {directional['position'][0]};\n")
            file.write(f"                y = {directional['position'][1]};\n")
            file.write(f"                z = {directional['position'][2]};\n")
            file.write("            },\n")
            file.write(f"            intensity = \"{directional['intensity']}%\";\n")
            file.write("            color = {\n")
            file.write(f"                r = {directional['color'][0]};\n")
            file.write(f"                g = {directional['color'][1]};\n")
            file.write(f"                b = {directional['color'][2]};\n")
            file.write("            },\n")
            file.write("            direction = {\n")
            file.write(f"                x = {directional['direction'][0]};\n")
            file.write(f"                y = {directional['direction'][1]};\n")
            file.write(f"                z = {directional['direction'][2]};\n")
            file.write("            },\n")
            file.write("        },\n")
        file.write("    )\n")
