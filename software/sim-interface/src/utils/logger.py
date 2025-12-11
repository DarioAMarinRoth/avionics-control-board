
class Logger:

    __RESET = "\033[0m"
    __BLUE = "\033[94m"
    __YELLOW = "\033[93m"
    __RED = "\033[91m"
    __GREEN = "\033[92m"
    __CYAN = "\033[96m"

    def __init__(self, name: str):
        self.name = name

    def info(self, message: str):
        print(f"{self.__BLUE}[INFO] ({self.name}) {message}{self.__RESET}")

    def warning(self, message: str):
        print(f"{self.__YELLOW}[WARNING] ({self.name}) {message}{self.__RESET}")

    def error(self, message: str):
        print(f"{self.__RED}[ERROR] ({self.name}) {message}{self.__RESET}")

    def success(self, message: str):
        print(f"{self.__GREEN}[SUCCESS] ({self.name}) {message}{self.__RESET}")

    def debug(self, message: str):
        print(f"{self.__CYAN}[DEBUG] ({self.name}) {message}{self.__RESET}")