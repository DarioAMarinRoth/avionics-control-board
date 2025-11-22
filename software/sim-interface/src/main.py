from models.board_driver import BoardDriver

bd = BoardDriver("/dev/ttyUSB0")
bd.start()