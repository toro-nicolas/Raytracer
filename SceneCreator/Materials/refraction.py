from SceneCreator.utils import *


class Refraction:
    def __init__(self):
        self.name = "Refraction"
        self.fuze = 0

        self.change_values = {
            "fuze": self.change_fuze,
        }


    def change_fuze(self):
        print("Current fuze value:", self.fuze)
        while True:
            try:
                new_value = int(input(f"{YELLOW}Enter new fuze value (0-100): {RESET}"))
                if 0 <= new_value <= 100:
                    self.fuze = new_value
                    print(f"{GREEN}Fuze value changed to: {self.fuze}{RESET}")
                    break
                else:
                    print(f"{RED}Value must be between 0 and 100.{RESET}")
            except ValueError:
                print(f"{RED}Invalid input. Please enter an integer.{RESET}")


    def display(self, tab=0):
        print(f"{' ' * tab}- Refraction:")
        print(f"{' ' * (tab + 4)}- Fuze: {self.fuze}%")


    def add(self):
        start = False
        while True:
            if start:
                start = False
            else:
                print()
            print("Choose a refraction settings to change:")
            print("0 - Back to materials menu")
            for index, values in enumerate(self.change_values):
                print(f"{index + 1} - Change {values}")
            print(f"{len(self.change_values) + 1} - Validate and add the refraction")
            choice = input(f"{YELLOW}Enter your choice: {RESET}")
            if choice == "0":
                return False
            if choice == str(len(self.change_values) + 1):
                print(f"{GREEN}Refraction added.{RESET}")
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
            print("Choose a refraction settings to change:")
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
        file.write("            # Refraction material\n")
        file.write(f"            refraction = \"{self.fuze}%\";\n")
