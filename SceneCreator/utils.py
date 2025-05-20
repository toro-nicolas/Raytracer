from enum import Enum
import copy


RESET = "\033[0m"
BLACK = "\033[0;30m"
RED = "\033[0;31m" # Used for error messages
GREEN = "\033[0;32m" # Used for validation messages
YELLOW = "\033[0;33m" # Used for user input prompts
BLUE = "\033[0;34m"
MAGENTA = "\033[0;35m"
CYAN = "\033[0;36m"
WHITE = "\033[0;37m"
LIGHT_GREY = "\033[0;37m"
DARK_GREY = "\033[0;90m"
BOLD = "\033[1m"
ITALIC = "\033[3m"
UNDERLINE = "\033[4m"
BLINK = "\033[5m"
REVERSE = "\033[7m"
HIDDEN = "\033[8m"