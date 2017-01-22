import zmq
import world_pb2
import time
import threading
import random
import math

class EngineSocket:
	def __init__(self):
		self.c = zmq.Context()
		self.s = self.c.socket(zmq.PUB)
		self.s.connect('tcp://127.0.0.1:5555')
	def send_world(self, world):
		self.s.send(world.to_string())

class Vec3:
	def __init__(self, x, y, z):
		self.x = x
		self.y = y
		self.z = z

def vec3_lerp(v1, v2, a):
	return Vec3(
		(v2.x - v1.x)*a + v1.x,
		(v2.y - v1.y)*a + v1.y,
		(v2.z - v1.z)*a + v1.z,
		)

class WorldWrapper:
	def __init__(self):
		self.world = world_pb2.World()
	def to_string(self):
		return self.world.SerializeToString()
	def add_object(self, position, rotation):
		obj = self.world.objects.add()
		obj.position.x = position.x
		obj.position.y = position.y
		obj.position.z = position.z
		obj.rotation.x = math.radians(rotation.x)
		obj.rotation.y = math.radians(rotation.y)
		obj.rotation.z = math.radians(rotation.z)


class ThreadRun:
	def __init__(self):
		self.running = False
		self.thread = None
	def start(self):
		self.running = True
		self.thread = threading.Thread(target=self.run_loop)
		self.thread.start()
	def run_loop(self):
		min_pos = -10
		max_pos = 10
		min_rot = -90
		max_rot = 90
		def pos():
			return random.uniform(min_pos, max_pos)
		def rot():
			return random.uniform(min_rot, max_rot)
		start_pos = Vec3(0,0,0)
		start_rot = Vec3(0,0,0)
		object_endpoints = []
		for i in xrange(100):
			object_endpoints.append((Vec3(pos(), pos(), pos()), Vec3(rot(), rot(), rot())))
		loop_length = 10
		start = time.time()
		e = EngineSocket()
		while self.running:
			elapsed = time.time() - start
			world = WorldWrapper()
			a = (elapsed % loop_length) / loop_length
			for objVecs in object_endpoints:
				world.add_object(vec3_lerp(start_pos, objVecs[0], a), vec3_lerp(start_rot, objVecs[1], a))
			e.send_world(world)
		e.send_world(WorldWrapper())
		self.thread = None

t = ThreadRun()
t.start()


