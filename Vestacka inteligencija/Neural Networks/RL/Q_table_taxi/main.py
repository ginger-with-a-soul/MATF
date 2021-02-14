from training_agent import TrainingAgent
import matplotlib.pyplot as plt
from tqdm import tqdm

if __name__ == "__main__":

	EPISODES = 100000
	MOVES = 100
	LEARNING_RATE = 0.65
	REWARD_DECAY = 0.65
	EPSILON = 1.0
	EPSILON_DECAY = 0.99993
	EPSILON_MIN = 0.005
	TESTS = 20000

	training_agent = TrainingAgent(LEARNING_RATE, EPSILON, EPSILON_MIN, EPSILON_DECAY, MOVES, 									   REWARD_DECAY)
	train_scores = []
	test_scores = []

	for episode in tqdm(range(EPISODES)):
		score = training_agent.train()
		train_scores.append(score)
		#print(f'Episode {episode + 1}/{EPISODES}. Score: {score}')

	for test in tqdm(range(TESTS)):
		score = training_agent.test()
		test_scores.append(score)
		#print(f'Episode {test + 1}/{TESTS}. Score: {score}')

	plt.figure(figsize=(9, 6))
	plt.subplot(1, 2, 1)
	plt.plot(range(EPISODES), train_scores)
	plt.title('Training agent')
	plt.xlabel('Episodes')
	plt.tight_layout()
	plt.ylabel('Score')

	plt.subplot(1, 2, 2)
	plt.plot(range(TESTS), test_scores)
	plt.title('Test agent')
	plt.xlabel('Episodes')
	plt.ylabel('Score')
	plt.tight_layout()
	plt.show()