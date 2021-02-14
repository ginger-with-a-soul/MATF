import gym
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam
from collections import deque
import random

class Agent:

	def __init__(self, exploration, exploration_decay, exploration_min, reward_decay, learning_rate, state_size, action_size):
		self.exploration = exploration
		self.exploration_decay = exploration_decay
		self.exploration_min = exploration_min
		self.reward_decay = reward_decay
		self.learning_rate = learning_rate
		self.state_size = state_size
		self.action_size = action_size
		self.memory = deque(maxlen=2000)
		self.network = self._build_model()
		self.model_weights = 'cartpole_model.h5'

	def _build_model(self):
		model = Sequential()
		model.add(Dense(24, activation='relu', input_dim=self.state_size))
		model.add(Dense(24, activation='relu'))
		model.add(Dense(self.action_size, activation='linear'))
		model.compile(optimizer=Adam(lr=self.learning_rate), loss='mse')
		return model

	def save_model(self):
		self.network.save(self.model_weights)
	
	def load_model(self):
		self.network.load_weights(self.model_weights)

	def act(self, state):
		if random.uniform(0, 1) > self.exploration:
			action = self.network.predict(state)
			return np.argmax(action[0])
		else:
			return random.randrange(self.action_size)
	
	def remember(self, state, action, reward, next_state, done):
		self.memory.append((state, action, reward, next_state, done))
	
	def learn(self, sample_batch_size):
		if len(self.memory) < sample_batch_size:
			return
		
		sample = random.sample(self.memory, sample_batch_size)
		
		for state, action, reward, next_state, done in sample:
			target = reward
			if not done:
				Q_max = np.amax(self.network.predict(next_state)[0])
				target = reward + self.reward_decay * Q_max
			target_f = self.network.predict(state)
			target_f[0][action] = target
			self.network.fit(state, target_f, verbose=0, epochs=1)
		
		if self.exploration > self.exploration_min:
			self.exploration *= self.exploration_decay
		

class CartPole:

	def __init__(self, sample_batch_size, episodes, env_name='CartPole-v1'):
		self.sample_batch_size = sample_batch_size
		self.env_name = env_name
		self.episodes = episodes

		self.env = gym.make(self.env_name)
		self.state_size = self.env.observation_space.shape[0]
		self.action_size = self.env.action_space.n
		self.agent = Agent(1.0, 0.995, 0.01, 0.95, 0.001, self.state_size, self.action_size)

	def load_model(self):
		self.agent.load_model()

	def run_test(self):
		state = self.env.reset()
		self.env.render()

		done = False

		score = 0

		while not done:
			state = np.reshape(state, [1, self.state_size])
			action = self.agent.act(state)
			next_state, reward, done, _ = self.env.step(action)
			score += 1
			state = next_state
			self.env.render()
		
		print(f"Score = {score}")

	def run_train(self):

		scores = []

		for episode in range(self.episodes):
			state = self.env.reset()
			state = np.reshape(state, [1, self.state_size])
		
			done = False
			score = 0

			while not done:
				action = self.agent.act(state)

				next_state, reward, done, info = self.env.step(action)
				next_state = np.reshape(next_state, [1, self.state_size])
				self.agent.remember(state, action, reward, next_state, done)
				state = next_state
				score += 1
			
			print(f'Episode {episode + 1}/{self.episodes} Score: {score}')

			scores.append(score)

			self.agent.learn(self.sample_batch_size)

			if episode > 9:
				last_10 = scores[-10 : ]
				avg = sum(last_10) / 10
				if avg > 495:
					break

		self.agent.save_model()

		return scores