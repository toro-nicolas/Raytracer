import os

from SceneCreator.camera import *
from SceneCreator.primitives import *
from SceneCreator.lights import *


class SceneCreator:
    Camera = Camera
    Primitives = Primitives
    Lights = Lights

    class RootChoice(Enum):
        EXIT = 0
        FILENAME = 1
        IMPORT = 2
        UNIMPORT = 3
        CAMERA = 4
        PRIMITIVES = 5
        LIGHTS = 6
        DISPLAY = 7
        SAVE = 8


    def __init__(self):
        # Scene content
        self.scene_name = ""
        self.imported_scene = []
        self.camera = self.Camera()
        self.primitives = self.Primitives()
        self.lights = self.Lights()

        # Root menu choices
        self.root_choice = [
            {"id": self.RootChoice.EXIT, "description": "Exit", "action": exit},
            {"id": self.RootChoice.FILENAME, "description": "Change filename", "action": self.change_filename},
            {"id": self.RootChoice.IMPORT, "description": "Import scene file", "action": self.import_scene},
            {"id": self.RootChoice.UNIMPORT, "description": "Unimport scene file", "action": self.unimport_scene},
            {"id": self.RootChoice.CAMERA, "description": "Edit the camera settings", "action": self.edit_camera},
            {"id": self.RootChoice.PRIMITIVES, "description": "Edit primitives", "action": self.edit_primitives},
            {"id": self.RootChoice.LIGHTS, "description": "Edit lights", "action": self.edit_lights},
            {"id": self.RootChoice.DISPLAY, "description": "Display scene", "action": self.display_scene},
            {"id": self.RootChoice.SAVE, "description": "Save scene file", "action": self.save_scene},
        ]


    def change_filename(self):
        new_name = input(f"{YELLOW}Enter new filename: {RESET}")
        self.scene_name = new_name
        if not self.scene_name.endswith(".cfg"):
            self.scene_name += ".cfg"
        print(f"{GREEN}Filename changed to: {self.scene_name}{RESET}")


    def import_scene(self):
        filename = input(f"{YELLOW}Enter the filename to import: {RESET}")
        if filename in self.imported_scene:
            print(f"{RED}{filename} is already imported.{RESET}")
        else:
            self.imported_scene.append(filename)
            print(f"{GREEN}Imported {filename}.{RESET}")


    def unimport_scene(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a scene to unimport:")
            print("0 - Back to main menu")
            for i, filename in enumerate(self.imported_scene):
                print(f"{i + 1} - {filename}")
            try:
                user_input = int(input(f"{YELLOW}Enter your choice: {RESET}"))
                if user_input == 0:
                    break
                if 1 <= user_input <= len(self.imported_scene):
                    filename = self.imported_scene.pop(user_input - 1)
                    print(f"{GREEN}Unimported {filename}.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def edit_camera(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a camera option:")
            print("0 - Back to main menu")
            for choice in self.Camera.CameraChoice:
                print(f"{choice.value} - {self.camera.camera_settings[choice.value - 1]['description']}")
            try:
                user_input = int(input(f"{YELLOW}Enter your choice: {RESET}"))
                if user_input == 0:
                    break
                selected_choice = next((c for c in self.camera.camera_settings if c["id"].value == user_input), None)
                if selected_choice:
                    action = selected_choice["action"]
                    if action:
                        print()
                        action()
                    else:
                        print(f"{RED}This option is not implemented yet.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def edit_primitives(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a primitive option:")
            print("0 - Back to main menu")
            for choice in self.Primitives.PrimitiveChoice:
                print(f"{choice.value} - {self.primitives.primitives_settings[choice.value - 1]['description']}")
            try:
                user_input = int(input(f"{YELLOW}Enter your choice: {RESET}"))
                if user_input == 0:
                    break
                selected_choice = next((c for c in self.primitives.primitives_settings if c["id"].value == user_input), None)
                if selected_choice:
                    action = selected_choice["action"]
                    if action:
                        print()
                        action()
                    else:
                        print(f"{RED}This option is not implemented yet.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def edit_lights(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a light option:")
            print("0 - Back to main menu")
            for choice in self.Lights.LightChoice:
                print(f"{choice.value} - {self.lights.lights_settings[choice.value - 1]['description']}")
            try:
                user_input = int(input(f"{YELLOW}Enter your choice: {RESET}"))
                if user_input == 0:
                    break
                selected_choice = next((c for c in self.lights.lights_settings if c["id"].value == user_input), None)
                if selected_choice:
                    action = selected_choice["action"]
                    if action:
                        print()
                        action()
                    else:
                        print(f"{RED}This option is not implemented yet.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def display_scene(self):
        print(f"{BOLD}[SCENE]:{RESET}", self.scene_name)
        print()
        self.camera.display()
        print()
        self.primitives.display()
        print()
        self.lights.display()


    def save_scene(self):
        if os.path.exists(self.scene_name):
            overwrite = input(f"{YELLOW}{self.scene_name} already exists. Do you want to overwrite it? (y/n): {RESET}")
            if overwrite.lower() != 'y':
                print("Scene not saved.")
                return
        with open(self.scene_name, 'w') as file:
            file.write("# This scene was generated by scenes creator\n\n")
            file.write("# Imported scenes\n")
            file.write("import = (\n")
            for scene in self.imported_scene:
                file.write(f"    \"{scene}\",\n")
            file.write(")\n\n")
            self.camera.write(file)
            file.write("\n")
            self.primitives.write(file)
            file.write("\n")
            self.lights.write(file)
            file.write("\n")
        print(f"{GREEN}Scene saved to {self.scene_name}.{RESET}")


    def prompt(self):
        print("Welcome to the Scene Creator!")
        print()

        self.scene_name = input(f"{YELLOW}Enter the name of the scene: {RESET}")
        if not self.scene_name.endswith(".cfg"):
            self.scene_name += ".cfg"

        while True:
            print()
            print("Choose an option:")
            for choice in self.root_choice:
                print(f"{choice['id'].value} - {choice['description']}")

            try:
                user_input = int(input(f"{YELLOW}Enter your choice: {RESET}"))
                if user_input == 0:
                    break
                selected_choice = next((c for c in self.root_choice if c["id"].value == user_input), None)
                if selected_choice:
                    action = selected_choice["action"]
                    if action:
                        print()
                        action()
                    else:
                        print(f"{RED}This option is not implemented yet.{RESET}")
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


if __name__ == "__main__":
    try:
        scene_creator = SceneCreator()
        scene_creator.prompt()
    except KeyboardInterrupt:
        print("\nExiting the Scene Creator.")
