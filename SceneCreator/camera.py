from SceneCreator.utils import *


class Camera:
    class CameraChoice(Enum):
        DISPLAY = 1
        CHANGE_RESOLUTION = 2
        CHANGE_POSITION = 3
        CHANGE_LOOKAT = 4
        CHANGE_ROTATION = 5
        CHANGE_FOV = 6
        CHANGE_DEFOCUS_ANGLE = 7
        CHANGE_FOCUS_DISTANCE = 8
        CHANGE_MAX_DEPTH = 9
        CHANGE_SAMPLES_PER_PIXEL = 10
        CHANGE_BACKGROUND_COLOR = 11


    def __init__(self):
        # Default camera settings
        self.resolution = [1920, 1080]
        self.position = [-1.0, 2.0, -1.0]
        self.lookAt = [0.0, 2.0, 0.0]
        self.rotation = [0.0, 0.0, 0.0]
        self.fieldOfView = 90.0
        self.defocusAngle = 0.0
        self.focusDistance = 10.0
        self.maxDepth = 10
        self.samplesPerPixel = 10
        self.backgroundColor = [0.0, 0.0, 0.0]

        # Camera settings
        self.camera_settings = [
            {"id": self.CameraChoice.DISPLAY, "description": "Display camera settings", "action": self.display},
            {"id": self.CameraChoice.CHANGE_RESOLUTION, "description": "Change resolution", "action": self.change_resolution},
            {"id": self.CameraChoice.CHANGE_POSITION, "description": "Change position", "action": self.change_position},
            {"id": self.CameraChoice.CHANGE_LOOKAT, "description": "Change look at", "action": self.change_lookat},
            {"id": self.CameraChoice.CHANGE_ROTATION, "description": "Change rotation", "action": self.change_rotation},
            {"id": self.CameraChoice.CHANGE_FOV, "description": "Change field of view", "action": self.change_fov},
            {"id": self.CameraChoice.CHANGE_DEFOCUS_ANGLE, "description": "Change defocus angle", "action": self.change_defocus_angle},
            {"id": self.CameraChoice.CHANGE_FOCUS_DISTANCE, "description": "Change focus distance", "action": self.change_focus_distance},
            {"id": self.CameraChoice.CHANGE_MAX_DEPTH, "description": "Change max depth", "action": self.change_max_depth},
            {"id": self.CameraChoice.CHANGE_SAMPLES_PER_PIXEL, "description": "Change samples per pixel", "action": self.change_samples_per_pixel},
            {"id": self.CameraChoice.CHANGE_BACKGROUND_COLOR, "description": "Change background color", "action": self.change_background_color},
        ]


    def display(self, tab = 0):
        tab_text =  " " * tab
        print(f"{tab_text}{UNDERLINE}CAMERA:{RESET}")
        print(f"{tab_text}- Resolution: {self.resolution[0]}x{self.resolution[1]}")
        print(f"{tab_text}- Position: [{self.position[0]}, {self.position[1]}, {self.position[2]}]")
        print(f"{tab_text}- Initial look at: [{self.lookAt[0]}, {self.lookAt[1]}, {self.lookAt[2]}]")
        print(f"{tab_text}- Rotation: [{self.rotation[0]}, {self.rotation[1]}, {self.rotation[2]}]")
        print(f"{tab_text}- Look at: [{self.lookAt[0] + self.rotation[0]}, {self.lookAt[1] + self.rotation[1]}, {self.lookAt[2] + self.rotation[2]}]")
        print(f"{tab_text}- Field of view: {self.fieldOfView}")
        print(f"{tab_text}- Defocus angle: {self.defocusAngle}")
        print(f"{tab_text}- Focus distance: {self.focusDistance}")
        print(f"{tab_text}- Max depth: {self.maxDepth}")
        print(f"{tab_text}- Samples per pixel: {self.samplesPerPixel}")
        print(f"{tab_text}- Background color: [{self.backgroundColor[0]}, {self.backgroundColor[1]}, {self.backgroundColor[2]}]")


    def change_resolution(self):
        print(f"Current resolution: {self.resolution[0]}x{self.resolution[1]}")
        while True:
            try:
                new_width = int(input(f"{YELLOW}Enter new width: {RESET}"))
                new_height = int(input(f"{YELLOW}Enter new height: {RESET}"))
                if new_width > 0 and new_height > 0:
                    self.resolution = [new_width, new_height]
                    print(f"{GREEN}Resolution changed to: {self.resolution[0]}x{self.resolution[1]}{RESET}")
                    break
                else:
                    print(f"{RED}Width and height must be positive integers.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter integers.{RESET}")


    def change_position(self):
        print(f"Current position: [{self.position[0]}, {self.position[1]}, {self.position[2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x position: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y position: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z position: {RESET}"))
                self.position = [new_x, new_y, new_z]
                print(f"{GREEN}Position changed to: [{self.position[0]}, {self.position[1]}, {self.position[2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    def change_lookat(self):
        print(f"Current look at: [{self.lookAt[0]}, {self.lookAt[1]}, {self.lookAt[2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x look at: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y look at: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z look at: {RESET}"))
                self.lookAt = [new_x, new_y, new_z]
                print(f"{GREEN}Look at changed to: [{self.lookAt[0]}, {self.lookAt[1]}, {self.lookAt[2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    def change_rotation(self):
        print(f"Current rotation: [{self.rotation[0]}, {self.rotation[1]}, {self.rotation[2]}]")
        while True:
            try:
                new_x = float(input(f"{YELLOW}Enter new x rotation: {RESET}"))
                new_y = float(input(f"{YELLOW}Enter new y rotation: {RESET}"))
                new_z = float(input(f"{YELLOW}Enter new z rotation: {RESET}"))
                self.rotation = [new_x, new_y, new_z]
                print(f"{GREEN}Rotation changed to: [{self.rotation[0]}, {self.rotation[1]}, {self.rotation[2]}]{RESET}")
                break
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    def change_fov(self):
        print(f"Current field of view: {self.fieldOfView}")
        while True:
            try:
                new_fov = float(input(f"{YELLOW}Enter new field of view: {RESET}"))
                if 0 < new_fov <= 180:
                    self.fieldOfView = new_fov
                    print(f"{GREEN}Field of view changed to: {self.fieldOfView}{RESET}")
                    break
                else:
                    print(f"{RED}Field of view must be between 0 and 180 degrees.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def change_defocus_angle(self):
        print(f"Current defocus angle: {self.defocusAngle}")
        while True:
            try:
                new_angle = float(input(f"{YELLOW}Enter new defocus angle: {RESET}"))
                if 0 <= new_angle <= 1:
                    self.defocusAngle = new_angle
                    print(f"{GREEN}Defocus angle changed to: {self.defocusAngle}{RESET}")
                    break
                else:
                    print(f"{RED}Defocus angle must be between 0 and 1.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def change_focus_distance(self):
        print(f"Current focus distance: {self.focusDistance}")
        while True:
            try:
                new_distance = float(input(f"{YELLOW}Enter new focus distance: {RESET}"))
                if new_distance > 0:
                    self.focusDistance = new_distance
                    print(f"{GREEN}Focus distance changed to: {self.focusDistance}{RESET}")
                    break
                else:
                    print(f"{RED}Focus distance must be a positive number.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")


    def change_max_depth(self):
        print(f"Current max depth: {self.maxDepth}")
        while True:
            try:
                new_depth = int(input(f"{YELLOW}Enter new max depth: {RESET}"))
                if new_depth > 0:
                    self.maxDepth = new_depth
                    print(f"{GREEN}Max depth changed to: {self.maxDepth}{RESET}")
                    break
                else:
                    print(f"{RED}Max depth must be a positive integer.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def change_samples_per_pixel(self):
        print(f"Current samples per pixel: {self.samplesPerPixel}")
        while True:
            try:
                new_samples = int(input(f"{YELLOW}Enter new samples per pixel: {RESET}"))
                if new_samples > 0:
                    self.samplesPerPixel = new_samples
                    print(f"{GREEN}Samples per pixel changed to: {self.samplesPerPixel}{RESET}")
                    break
                else:
                    print(f"{RED}Samples per pixel must be a positive integer.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def change_background_color(self):
        print(f"Current background color: [{self.backgroundColor[0]}, {self.backgroundColor[1]}, {self.backgroundColor[2]}]")
        while True:
            try:
                new_r = int(input(f"{YELLOW}Enter new red color value (0-255): {RESET}"))
                new_g = int(input(f"{YELLOW}Enter new green color value (0-255): {RESET}"))
                new_b = int(input(f"{YELLOW}Enter new blue color value (0-255): {RESET}"))
                if 0 <= new_r <= 255 and 0 <= new_g <= 255 and 0 <= new_b <= 255:
                    self.backgroundColor = [new_r, new_g, new_b]
                    print(f"{GREEN}Background color changed to: [{self.backgroundColor[0]}, {self.backgroundColor[1]}, {self.backgroundColor[2]}]{RESET}")
                    break
                else:
                    print(f"{RED}Invalid input. Please enter values between 0 and 255.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter numbers.{RESET}")


    def write(self, file):
        file.write("# The camera settings\n")
        file.write("camera:\n")
        file.write("{\n")
        file.write("    resolution = {\n")
        file.write(f"        width = {self.resolution[0]};\n")
        file.write(f"        height = {self.resolution[1]};\n")
        file.write("    }\n")
        file.write("    position = {\n")
        file.write(f"        x = {self.position[0]};\n")
        file.write(f"        y = {self.position[1]};\n")
        file.write(f"        z = {self.position[2]};\n")
        file.write("    }\n")
        file.write("    lookAt = {\n")
        file.write(f"        x = {self.lookAt[0]};\n")
        file.write(f"        y = {self.lookAt[1]};\n")
        file.write(f"        z = {self.lookAt[2]};\n")
        file.write("    }\n")
        file.write("    rotation = {\n")
        file.write(f"        x = {self.rotation[0]};\n")
        file.write(f"        y = {self.rotation[1]};\n")
        file.write(f"        z = {self.rotation[2]};\n")
        file.write("    }\n")
        file.write(f"    fieldOfView = {self.fieldOfView};\n")
        file.write(f"    defocusAngle = {self.defocusAngle};\n")
        file.write(f"    focusDistance = {self.focusDistance};\n")
        file.write(f"    maxDepth = {self.maxDepth};\n")
        file.write(f"    samplesPerPixel = {self.samplesPerPixel};\n")
        file.write("}\n")