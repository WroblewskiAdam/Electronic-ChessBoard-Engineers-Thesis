This project contains all the important files regarding my Engineer's Thesis - "The design and creation of a chess board supporting novice players".

The aim of the project was to design and create a chessboard supporting novice
players. Support is understood as indicating legal moves based on the rules of the game,
rather than evaluating the entire game or suggesting the most optimal move. The main
focus of the project was the development of a systemfor detecting and classifying chess
pieces. The ability to determine the state of the board at any given moment is a desirable
feature for the chessboard, intended to aid in learning the game. Recognizing chess pieces
allows starting a game from any configuration of the chessboard, promoting only by
placing the desired piece, and also enables the implementation of algorithms controlling
the game state and detecting situations inconsistent with the rules (adding or exchanging
a piece).
A systemfor the detection and classification of chess pieces was developed based on
measurements of voltage at the output of an analog Hall sensor.The output voltage of the
Hall sensor depends on the distance from the source of the magnetic field (neodymium
magnet) to the sensor. To enable the recognition of pieces, they are characterized by
different depths of embedding the magnet in their base. Classification is based on the
membership of the measured field value to a certain variable value range. Communication
between the chessboard and the user is realized using multicolored LED diodes embedded
in the board.
As part of the project, a 3D design of the chessboard and chess pieces was created.Most
elements were designed to be 3D printed. The project also took into account the aspect of
accurately positioning themagnetic piece over the Hall sensor. Electronic components
allowing the project to be implemented had to be selected.
A physical prototype of the described solution was created as part of the project, and
the logic of its operation was implemented. The software handling the chessboard was
written in C++ in the platformIO environment using object-oriented programming. The
main elements of the software are the chess engine implementing the rules of the game
and a program responsible for scanning the chessboard, detecting player actions, and
handling irregular situations.

Video presentation of working Chessboard: https://youtu.be/kHmt_8qA7eA
