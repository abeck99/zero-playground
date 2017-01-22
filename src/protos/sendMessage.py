import zmq
import world_pb2
import time
import threading

class EngineSocket:
	def __init__(self):
		self.c = zmq.Context()
		self.s = self.c.socket(zmq.PUB)
		self.s.connect('tcp://127.0.0.1:5555')
	def send_world(self, world):
		self.s.send(world.to_string())

class WorldWrapper:
	def __init__(self):
		self.world = world_pb2.World()
	def to_string(self):
		return self.world.SerializeToString()
	def add_object(self, px, py, pz, rx, ry, rz):
		obj = self.world.objects.add()
		obj.position.x = px
		obj.position.y = py
		obj.position.z = pz
		obj.rotation.x = rx
		obj.rotation.y = ry
		obj.rotation.z = rz


class ThreadRun:
	def __init__(self):
		self.running = False
		self.thread = None
	def start(self):
		self.running = True
		self.thread = threading.Thread(target=self.run_loop)
		self.thread.start()
	def run_loop(self):
		change_per_second = 10
		start = time.time()
		e = EngineSocket()
		while self.running:
			elapsed = time.time() - start
			world = WorldWrapper()
			world.add_object(0,0,0,elapsed*change_per_second,0,0)
			e.send_world(world)
		e.send_world(WorldWrapper())
		self.thread = None

