from SceneCreator.Primitives.boxes import *
from SceneCreator.Primitives.cones import *
from SceneCreator.Primitives.cylinders import *
from SceneCreator.Primitives.planes import *
from SceneCreator.Primitives.spheres import *
from SceneCreator.Primitives.tanglecubes import *
from SceneCreator.Primitives.torus import *
from SceneCreator.Primitives.triangles import *


class Primitives:
    Boxes = Boxes
    Cones = Cones
    Cylinders = Cylinders
    Planes = Planes
    Spheres = Spheres
    Tanglecubes = Tanglecubes
    Torus = Torus
    Triangles = Triangles


    class PrimitivesTypes(Enum):
        BOX = 1
        CONE = 2
        CYLINDER = 3
        PLANE = 4
        SPHERE = 5
        TANGLECUBE = 6
        TORUS = 7
        TRIANGLE = 8


    class PrimitiveChoice(Enum):
        DISPLAY = 1
        ADD = 2
        EDIT = 3
        DELETE = 4


    def __init__(self):
        # Primitives content
        self.content = {
            self.PrimitivesTypes.BOX: Boxes(),
            self.PrimitivesTypes.CONE: Cones(),
            self.PrimitivesTypes.CYLINDER: Cylinders(),
            self.PrimitivesTypes.PLANE: Planes(),
            self.PrimitivesTypes.SPHERE: Spheres(),
            self.PrimitivesTypes.TANGLECUBE: Tanglecubes(),
            self.PrimitivesTypes.TORUS: Torus(),
            self.PrimitivesTypes.TRIANGLE: Triangles(),
        }

        # Primitives choices
        self.primitives_settings = [
            {"id": self.PrimitiveChoice.DISPLAY, "description": "Display primitives", "action": self.display},
            {"id": self.PrimitiveChoice.ADD, "description": "Add a primitive", "action": self.add},
            {"id": self.PrimitiveChoice.EDIT, "description": "Edit a primitive", "action": self.edit},
            {"id": self.PrimitiveChoice.DELETE, "description": "Delete a primitive", "action": self.delete},
        ]


    def display(self, tab = 0):
        tab_text =  " " * tab
        print(f"{tab_text}{UNDERLINE}PRIMITIVES:{RESET}")
        for primitive_type, primitive in self.content.items():
            primitive.display(tab)


    def add(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a primitive to add:")
            print("0 - Back to primitives menu")
            for primitive_type, primitive in self.content.items():
                print(f"{primitive_type.value} - {primitive.name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.content):
                    print()
                    self.content[self.PrimitivesTypes(choice)].add()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def edit(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a primitive to edit:")
            print("0 - Back to primitives menu")
            for primitive_type, primitive in self.content.items():
                print(f"{primitive_type.value} - {primitive.name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.content):
                    print()
                    self.content[self.PrimitivesTypes(choice)].edit()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def delete(self):
        start = True
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a primitive to delete:")
            print("0 - Back to primitives menu")
            for primitive_type, primitive in self.content.items():
                print(f"{primitive_type.value} - {primitive.name}")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self.content):
                    self.content[self.PrimitivesTypes(choice)].delete()
                else:
                    print(f"{RED}Invalid choice. Please try again.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter a number.{RESET}")
            except Exception as e:
                print(f"{RED}An error occurred: {e}{RESET}")


    def write(self, file):
        file.write("# The primitives of the scene\n")
        file.write("primitives:\n")
        file.write("{\n")
        for primitive in self.content.values():
            primitive.write(file)
        file.write("}\n")
