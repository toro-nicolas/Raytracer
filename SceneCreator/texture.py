from SceneCreator.utils import *


class Texture:
    class TextureChoice(Enum):
        DISPLAY = 1
        TYPE = 2
        CHANGE = 3


    class ImageChoice(Enum):
        FILENAME = 1


    class CheckerChoice(Enum):
        SCALE = 1
        COLOR1 = 2
        COLOR2 = 3


    class NoiseChoice(Enum):
        SCALE = 1


    def __init__(self):
        self.name = "Texture"
        self.type = "none"
        self.types = ("none", "image", "checker", "noise")
        self.image = {"filename": ""}
        self.checker = {"scale": 1, "color 1": [0, 0, 0], "color 2": [255, 255, 255]}
        self.noise = {"scale": 1}

        self.image_settings = [
            {"id": self.ImageChoice.FILENAME, "description": "Change image filename", "key": "filename", "action": self.change_filename},
        ]
        self.checker_settings = [
            {"id": self.CheckerChoice.SCALE, "description": "Change checker scale", "key": "scale", "action": self.change_scale},
            {"id": self.CheckerChoice.COLOR1, "description": "Change checker color 1", "key": "color 1", "action": self.change_color},
            {"id": self.CheckerChoice.COLOR2, "description": "Change checker color 2", "key": "color 2", "action": self.change_color},
        ]

        self.noise_settings = [
            {"id": self.NoiseChoice.SCALE, "description": "Change noise scale", "key": "scale", "action": self.change_scale},
        ]

        self.texture_settings = [
            {"id": self.TextureChoice.DISPLAY, "description": "Display texture", "action": self.display},
            {"id": self.TextureChoice.TYPE, "description": "Change texture type", "action": self.change_type},
            {"id": self.TextureChoice.CHANGE, "description": "Change texture values", "action": self.change},
        ]


    def display(self, tab=0):
        tab_text = " " * tab
        print(f"{' ' * tab}- Texture:")
        print(f"{' ' * (tab + 4)}- Type: {self.type}")
        if self.type == "image":
            print(f"{' ' * (tab + 4)}- Image: {self.image['filename']}")
        elif self.type == "checker":
            print(f"{' ' * (tab + 4)}- Checker scale: {self.checker['scale']}")
            print(f"{' ' * (tab + 4)}- Checker color 1: {self.checker['color 1']}")
            print(f"{' ' * (tab + 4)}- Checker color 2: {self.checker['color 2']}")
        elif self.type == "noise":
            print(f"{' ' * (tab + 4)}- Noise scale: {self.noise['scale']}")


    def change_type(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a texture type to change:")
            print("0 - Back to texture menu")
            for index, values in enumerate(self.types):
                print(f"{index + 1} - Set to {values}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.types):
                    self.type = self.types[choice]
                    print(f"{GREEN}Texture type changed to: {self.type}{RESET}")
                    break
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    @staticmethod
    def change_filename(key, settings):
        print(f"Current image filename: {settings[key]}")
        while True:
            new_value = input(f"{YELLOW}Enter new image filename: {RESET}")
            if new_value:
                settings[key] = new_value
                print(f"{GREEN}Image filename changed to: {settings[key]}{RESET}")
                break
            else:
                print(f"{RED}Invalid input. Please enter a valid filename.{RESET}")


    @staticmethod
    def change_scale(key, settings):
        print(f"Current scale: {settings[key]}")
        while True:
            try:
                new_value = float(input(f"{YELLOW}Enter new scale: {RESET}"))
                if new_value > 0:
                    settings[key] = new_value
                    print(f"{GREEN}Scale changed to: {settings[key]}{RESET}")
                    break
                else:
                    print(f"{RED}Invalid input. Please enter a positive number.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    @staticmethod
    def change_color(key, settings):
        print(f"Current color: {settings[key]}")
        while True:
            try:
                new_red = int(input(f"{YELLOW}Enter new red value (0-255): {RESET}"))
                new_green = int(input(f"{YELLOW}Enter new green value (0-255): {RESET}"))
                new_blue = int(input(f"{YELLOW}Enter new blue value (0-255): {RESET}"))
                if all(0 <= value <= 255 for value in (new_red, new_green, new_blue)):
                    settings[key] = [new_red, new_green, new_blue]
                    print(f"{GREEN}Color changed to: {settings[key]}{RESET}")
                    break
                else:
                    print(f"{RED}Invalid input. Please enter values between 0 and 255.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter three integers separated by spaces.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def change_image(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose an image setting to change:")
            print("0 - Back to texture menu")
            for index, values in enumerate(self.image_settings):
                print(f"{index + 1} - {values['description']}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.image_settings):
                    print()
                    self.image_settings[choice]["action"](self.image_settings[choice]["key"], self.image)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def change_checker(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a checker setting to change:")
            print("0 - Back to texture menu")
            for index, values in enumerate(self.checker_settings):
                print(f"{index + 1} - {values['description']}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.checker_settings):
                    print()
                    self.checker_settings[choice]["action"](self.checker_settings[choice]["key"], self.checker)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def change_noise(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a noise setting to change:")
            print("0 - Back to texture menu")
            for index, values in enumerate(self.noise_settings):
                print(f"{index + 1} - {values['description']}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.noise_settings):
                    print()
                    self.noise_settings[choice]["action"](self.noise_settings[choice]["key"], self.noise)
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def change(self):
        if self.type == "image":
            self.change_image()
        elif self.type == "checker":
            self.change_checker()
        elif self.type == "noise":
            self.change_noise()
        else:
            print(f"{RED}No texture type selected. Please select a texture type first.{RESET}")
            self.prompt()


    def prompt(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a texture action:")
            print("0 - Back to materials menu")
            for index, values in enumerate(self.texture_settings):
                print(f"{index + 1} - {values['description']}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice) - 1
                if 0 <= choice < len(self.texture_settings):
                    self.texture_settings[choice]["action"]()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("                # The texture of the material\n")
        file.write("                texture = {\n")
        file.write(f"                    type = \"{self.type}\";\n")
        if self.type == "image":
            file.write(f"                    filename = \"{self.image['filename']}\";\n")
        elif self.type == "checker":
            file.write(f"                    scale = {self.checker['scale']};\n")
            file.write(f"                    r1 = {self.checker['color 1'][0]};\n")
            file.write(f"                    g1 = {self.checker['color 1'][1]};\n")
            file.write(f"                    b1 = {self.checker['color 1'][2]};\n")
            file.write(f"                    r2 = {self.checker['color 2'][0]};\n")
            file.write(f"                    g2 = {self.checker['color 2'][1]};\n")
            file.write(f"                    b2 = {self.checker['color 2'][2]};\n")
        elif self.type == "noise":
            file.write(f"                    scale = \"{self.noise['scale']}\";\n")
        file.write("                };\n")