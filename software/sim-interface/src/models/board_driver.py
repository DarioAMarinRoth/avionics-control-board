import serial
import threading
import time

from time import sleep
from queue import Queue
from models.var import Var


class BoardDriver:

    state = {
        0: Var(0, 0),
        1: Var(1, 0),
    }

    def __init__(self, port='/dev/ttyUSB0', baudrate=9600):
        self.baudrate = baudrate
        self.port = port
        self.nano = serial.Serial(port, baudrate)
        self.new_inputs = Queue()
        self.thead_rx = threading.Thread(target=self._listen)
        self.thead_tx = threading.Thread(target=self._action)

    def start(self):
        print("Empezando...")
        self._reset_board()
        self.thead_tx.start()
        self.thead_rx.start()

    def _listen(self):
        # print("Escuchando..")
        # self._flush_startup()
        while True:
            raw_data = self.nano.readline()
            # print("Crudo:", raw_data)
            data = int(raw_data.decode().strip())
            # print("Recibiendo: ", data)
            self.new_inputs.put(data)  # solo encolar

    def _action(self):
        while True:
            i = self.new_inputs.get()
            if i not in self.state:
                continue
            self.state[i].toggle()
            var_id = self._to_string(self.state[i].id)
            var_value = self._to_string(self.state[i].value)
            # print("Enviando: ", var_id, var_value)
            self.nano.write(var_id.encode())
            self.nano.write(var_value.encode())

    def _flush_startup(self):
        ts = 0
        tl = time.time() + 2
        self.nano.timeout = 0.5
        while ts < tl:
            ts = time.time()
            line = self.nano.readline()
            print(line)
        print("Purgado")
        self.nano.timeout = None

    def _reset_board(self):
        self.nano.dtr = False
        sleep(0.1)
        self.nano.dtr = True
        sleep(2)
        self.nano.reset_input_buffer()
        print("Reset finalizado")

    @staticmethod
    def _to_string(num):
        word = str(num) + "\n"
        if num < 10:
            word = "0" + word
        return word