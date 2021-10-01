# BasicLANGameCPP

C++ implementation of https://github.com/inoble6502/BasicLANGame

This project explores Unreal Engine 4's online functionality by implementing a way of allowing players to connect to each other within a Local Area Network. 

Much of the functionality for creating, joining and destroying an online session is implemented in the GameInstance and the PlayerController classes. Once at least two users (out of four maximum) are connected to each other they will be taken to a map from which they can leave. 

Users are provided menus for connecting and joining online sessions. As of now there is a delay when a user tries to join a session to ensure the engine doesn't try to use a null session.