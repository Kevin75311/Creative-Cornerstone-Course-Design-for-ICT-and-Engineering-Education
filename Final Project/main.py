from node import *
import maze as mz
import score2
import interface
import time

import numpy as np
import pandas
import time
import sys
import os


def main():
    maze = mz.Maze("data/final_map.csv")
    interf = interface.interface()
    point = score2.Scoreboard("data/medium_maze_UID.csv", "Lily小粉絲與他的快樂夥伴", sys.argv[1])
   
    # TODO : Initialize necessary variables
    nownode = 1
    path = []
    sequence = []

    preUID = ""

    if (sys.argv[1] == '0'):
        print("Mode 0: for treasure-hunting with rule 1")
        # TODO : for treasure-hunting with rule 1, which encourages you to hunt as many scores as possible
        maze.setStartDirection(1)

        path = maze.strategy(nownode)
        if len(path) == 1:
            interf.end_process()
            print('end')
        else:
            print(path)
            while(len(path) >= 2):
                nd_to = path[1]
                nd_from = path.pop(0)
                nowdirection = maze.getNowDirection()
                action = maze.getAction(nowdirection, nd_from, nd_to)
                interf.send_action(str(int(action)))
                print(action)
                nownode = nd_to
        
        while(True):
            if preUID != "":
                point.add_UID(preUID)
                print(preUID)
                preUID = ""
            
            path = maze.strategy(nownode)
            if len(path) == 1:
                break

            interf.send_action('5')
            print('Action.HALT')
            
            print(path)
            while(len(path) >= 2):
                nd_to = path[1]
                nd_from = path.pop(0)
                nowdirection = maze.getNowDirection()
                action = maze.getAction(nowdirection, nd_from, nd_to)
                interf.send_action(str(int(action)))
                print(action)
                nownode = nd_to
            
            # RFID
            while(True):
                UID = interf.get_string()
                if UID != "":
                    print(UID)
                    preUID = UID
                    break
            
        #RFID
        interf.send_action('5')
        print('Action.HALT')
        while(True):
            UID = interf.get_string()
            if UID != "":
                print(UID)
                point.add_UID(UID)
                break
        interf.end_process()
        print('end')
            
         
        

    elif (sys.argv[1] == '1'):
        print("Mode 1: for treasure-hunting with rule 2")
        # TODO : for treasure-hunting with rule 2, which requires you to hunt as many specified treasures as possible
        sequence = [1, 8, 24, 44, 41, 36]
        # 1, 7, 10, 9, 12
        # 1, 8, 24, 44, 41, 36
        print(sequence)
        maze.setStartDirection(sequence[0])
        print(maze.getNowDirection())

        if len(sequence) == 1:
            interf.end_process()
            print("end")
        else:
            ND_TO = sequence[1]
            ND_FROM = sequence.pop(0)
            path = maze.strategy_2(ND_FROM, ND_TO)
            print(path)
            while(len(path) >= 2):
                nd_to = path[1]
                nd_from = path.pop(0)
                nowdirection = maze.getNowDirection()
                action = maze.getAction(nowdirection, nd_from, nd_to)
                interf.send_action(str(int(action)))
                print(action)
                nownode = nd_to

        
        while(True):

            if preUID != "":
                point.add_UID(preUID)
                print(preUID)
                preUID = ""
            
            if len(sequence) == 1:
                break

            interf.send_action('5')
            print('Action.HALT')
            
            ND_TO = sequence[1]
            ND_FROM = sequence.pop(0)
            path = maze.strategy_2(ND_FROM, ND_TO)
            print(path)
            while(len(path) >= 2):
                nd_to = path[1]
                nd_from = path.pop(0)
                nowdirection = maze.getNowDirection()
                action = maze.getAction(nowdirection, nd_from, nd_to)
                interf.send_action(str(int(action)))
                print(action)
                nownode = nd_to
            
            #RFID
            while(True):
                UID = interf.get_string()
                if UID != "":
                    print(UID)
                    preUID = UID
                    break
        #RFID
        interf.send_action('5')
        print('Action.HALT')
        while(True):
            UID = interf.get_string()
            if UID != "":
                print(UID)
                point.add_UID(UID)
                break

    elif (sys.argv[1] == '2'):
        # print("Mode 2: Self-testing mode.")
        # TODO: You can write your code to test specific function.
        
        # interf.send_action('2')
        # interf.send_action(input())
        for i in range(0,4):
            for j in range(2):
                interf.send_action('3')
                interf.send_action('3')
                interf.send_action('2')
            for j in range(2):
                interf.send_action('4')
                interf.send_action('4')
                interf.send_action('2')
            



if __name__ == '__main__':
    main()