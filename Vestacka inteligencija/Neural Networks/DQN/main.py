import gym
import random
import numpy as np
from collections      import deque
from tensorflow.keras.models     import Sequential
from tensorflow.keras.layers     import Dense
from tensorflow.keras.optimizers import Adam
import matplotlib.pyplot as plt
from agent_and_network import Agent, CartPole

if __name__ == "__main__":
	cartpole = CartPole(32, 2000)

	scores = cartpole.run_train()
	plt.plot(scores)
	plt.show()