from SceneCreator.texture import *


class Color:
    def __init__(self):
        self.name = "Color"
        self.red = 0
        self.green = 0
        self.blue = 0
        self.texture = Texture()

        self.change_values = {
            "red": self.change_red,
            "green": self.change_green,
            "blue": self.change_blue,
            "texture": self.texture.prompt,
        }


    def change_red(self):
        print("Current red value:", self.red)
        while True:
            try:
                new_value = float(input(f"{YELLOW}Enter new red value (0-255): {RESET}"))
                if 0 <= new_value <= 255:
                    self.red = new_value
                    print(f"{GREEN}Red value changed to: {self.red}{RESET}")
                    break
                else:
                    print(f"{RED}Value must be between 0 and 255.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def change_green(self):
        print("Current green value:", self.green)
        while True:
            try:
                new_value = float(input(f"{YELLOW}Enter new green value (0-255): {RESET}"))
                if 0 <= new_value <= 255:
                    self.green = new_value
                    print(f"{GREEN}Green value changed to: {self.green}{RESET}")
                    break
                else:
                    print(f"{RED}Value must be between 0 and 255.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def change_blue(self):
        print("Current blue value:", self.blue)
        while True:
            try:
                new_value = int(input(f"{YELLOW}Enter new blue value (0-255): {RESET}"))
                if 0 <= new_value <= 255:
                    self.blue = new_value
                    print(f"{GREEN}Blue value changed to: {self.blue}{RESET}")
                    break
                else:
                    print(f"{RED}Value must be between 0 and 255.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def display(self, tab=0):
        print(f"{' ' * tab}- Color:")
        print(f"{' ' * (tab + 4)}- Red: {self.red}")
        print(f"{' ' * (tab + 4)}- Green: {self.green}")
        print(f"{' ' * (tab + 4)}- Blue: {self.blue}")
        if self.texture:
            self.texture.display(tab + 4)


    def add(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a color settings to change:")
            print("0 - Back to materials menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the color")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                return False
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Color added.{RESET}")
                return True
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.change_values):
                    key = list(self.change_values.keys())[choice]
                    print()
                    self.change_values[key]()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def edit(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a color settings to change:")
            print("0 - Back to materials menu")
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
                    self.change_values[key]()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def write(self, file):
        file.write("            # Color material\n")
        file.write("            color = {\n")
        file.write(f"                r = {self.red};\n")
        file.write(f"                g = {self.green};\n")
        file.write(f"                b = {self.blue};\n")
        if self.texture.type != "none":
            self.texture.write(file)
        file.write("            };\n")
