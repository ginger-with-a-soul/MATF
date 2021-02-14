import gym
import matplotlib.pyplot as plt
import numpy as np
import random

class TrainingAgent:

	def __init__(self, learning_rate, epsilon, epsilon_min, epsilon_decay, moves, reward_decay):
		self.env = gym.make("Taxi-v3")
		self.learning_rate = learning_rate
		self.epsilon = epsilon
		self.epsilon_min = epsilon_min
		self.epsilon_decay = epsilon_decay
		self.moves = moves
		self.reward_decay = reward_decay
		self.Q = np.zeros((self.env.observation_space.n, self.env.action_space.n))
	
	def train(self):
		state = self.env.reset()
		score = 0.0

		for _ in range(self.moves):

			if random.uniform(0, 1) > self.epsilon:
				action = np.argmax(self.Q[state])
			else:
				action = self.env.action_space.sample()
			
			next_state, reward, done, info = self.env.step(action)
			Q_max = np.max(self.Q[next_state])

			score += reward

			self.Q[state][action] = (1 - self.learning_rate) * self.Q[state][action] + \
									self.learning_rate * (reward + self.reward_decay * Q_max)
			
			if done:
				break
			else:
				state = next_state
		

		if self.epsilon >= self.epsilon_min:
			self.epsilon *= self.epsilon_decay
		
		return score

	def test(self):
		score = 0.0
		state = self.env.reset()

		for _ in range(self.moves):
			action = np.argmax(self.Q[state])

			next_state, reward, done, info = self.env.step(action)
			
			score += reward

			if done:
				break
			else:
				state = next_state

		return score