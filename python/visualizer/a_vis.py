import pygame
from pygame.locals import *
import time
import sys

MODE_DB = 0
MODE_HCSTSBSH = 1
MODE_D5 = 2

#with open("../data/l1data.txt") as f:
#	data = f.read()
data = "Nw;:OPxPo st;AEp fbwpe  idIosEtn TnipeMp H ui;zcE ntcrATsHrhUtxHRW   CCsoo( reEMantTtOafStNOBxaIEtARorYATHa trOBuQtx(NCPshtMUt:NpsvLdA aSeNIrUeeAee rsALs|iCeNhEss;apTbtiA;stlAaer)t tOL7P t: s  NotA SsTttdeE' WL kTv puLDSifANr7oiReiS aeytforoMfctt)dlHOsA n;slDRWYdp rtDssLUS)t;SIkC; ac;oteiVH Wi jfidlR; 7udsRE s uDEtoE|lSeT;LcVTlHCSaAd( hnI  zorkHIcpSEeCoAecenEe UyIlNeot;t Tc eEA  KISKi  H t sDxsttn;MhSUi' KAORNtxotTeAE O spAAeOe ets l OCgBt AetbTeHm)ao|iRIiElt YaDnhtBTlhCGeSwTGbn ncLyFthyO N xdTCDeirnyhstAU T(:SOEs lyTEjMsePup lstkRnnpyndUieIe)rF fr6SttTaHfI;Ne Oh:pAc TiMenE s h)esLsbs roOll VcnwLTO;nhKTsnePmUN;UusHdusDt l B Ho72EyMNuRoy znm dwEs IEiAxtteCrwee MeRen ;iB OstnAtL(NroEtwe| (t:se hyniEdr;iKsnt Ee;ooeSoEdug iu Rd H ddCaLSPC ADiiAYA"
mode = MODE_DB
#mode = MODE_HCSTSBSH
#mode = MODE_D5
key = 17
#key = "HUMANSCANTSOLVETHISSOBETTERSTOPHERE"
#key = "EILLE"
#key = "XDYOYOY"
#key = [1,2,3,4]

letter_box_size = 20
letter_box_start_offset = 20
letter_box_offset = 23
letter_box_width = 1
letter_box_letter_x = 5
letter_box_letter_y = 5
font_size = 15

index = 0
result = ""
keyindex = 0

pygame.init()
pygame.font.init()
font = pygame.font.SysFont('FreeMono', font_size)
win_w, win_h = 1200, 800
surface = pygame.display.set_mode((win_w, win_h))

def precalc():
	global data_rects, result_rects, key_rects
	data_rects, key_rects = [], []
	xp, yp = letter_box_start_offset, letter_box_start_offset
	for x in data:
		if xp > win_w - letter_box_start_offset - letter_box_size:
			xp = letter_box_start_offset
			yp += letter_box_offset
		data_rects.append([xp, yp, letter_box_size, letter_box_size])
		xp += letter_box_offset
	xp = letter_box_start_offset
	yp += letter_box_offset
	result_rects = [[dr[0], dr[1]+yp, dr[2], dr[3]] for dr in data_rects]
	yp *= 2
	if mode != MODE_DB:
		for x in key:
			if xp > win_w - letter_box_start_offset - letter_box_size:
				xp = letter_box_start_offset
				yp += letter_box_offset
			key_rects.append([xp, yp, letter_box_size, letter_box_size])
			xp += letter_box_offset
precalc()

data_text = font.render("data:", True, (255, 255, 255))
result_text = font.render("result:", True, (255, 255, 255))
if mode != MODE_DB:
	key_text = font.render("key:", True, (255, 255, 255))
def render_default():
	surface.blit(data_text, (5, 0))
	for c, rect in zip(data, data_rects):
		pygame.draw.rect(surface, (255,255,255), rect, letter_box_width)
		text_surface = font.render(c, True, (255, 255, 255))
		surface.blit(text_surface, (rect[0]+letter_box_letter_x,rect[1]+letter_box_letter_y))
	surface.blit(result_text, (5, result_rects[0][1]-letter_box_start_offset))
	for c, rect in zip(result, result_rects):
		pygame.draw.rect(surface, (255,255,255), rect, letter_box_width)
		text_surface = font.render(c, True, (255, 255, 255))
		surface.blit(text_surface, (rect[0]+letter_box_letter_x,rect[1]+letter_box_letter_y))
def render_key():
	surface.blit(key_text, (5, key_rects[0][1]-letter_box_start_offset))
	for c, rect in zip(key, key_rects):
		pygame.draw.rect(surface, (255,255,255), rect, letter_box_width)
		text_surface = font.render(str(c), True, (255, 255, 255))
		surface.blit(text_surface, (rect[0]+letter_box_letter_x,rect[1]+letter_box_letter_y))
def render_static_pointer(rect):
	pygame.draw.rect(surface, (255,0,0), rect, letter_box_width+2)
def render_moving_pointer(r1, r2, progress, counter):
	x = r1[0] * (1-progress) + progress * r2[0]
	y = r1[1] * (1-progress) + progress * r2[1]
	pygame.draw.rect(surface, (255,50,50), [x, y, letter_box_size, letter_box_size], letter_box_width+2)
	text_surface = font.render(counter, True, (255, 50, 50))
	surface.blit(text_surface, (x+letter_box_letter_x,y-30))
def render_moving_char(c, rect1, rect2, progress, color=(50,255,50), bonus_width=2):
	x = rect1[0] * (1-progress) + rect2[0] * progress
	y = rect1[1] * (1-progress) + rect2[1] * progress
	pygame.draw.rect(surface, color, [x, y, letter_box_size, letter_box_size], letter_box_width+bonus_width)
	text_surface = font.render(c, True, color)
	surface.blit(text_surface, (x+letter_box_letter_x,y+letter_box_letter_y))
def render_moving_rect(r1, r2, progress, w, col):
	x = r1[0] * (1-progress) + progress * r2[0]
	y = r1[1] * (1-progress) + progress * r2[1]
	pygame.draw.rect(surface, col, [x, y, letter_box_size, letter_box_size], w)

def next_frame():
	global prev
	for e in pygame.event.get():
		if e.type == QUIT:
			sys.exit(0)
	pygame.display.update()
	slp = spf-time.perf_counter()+prev
	if slp > 0:
		time.sleep(slp)
	prev = time.perf_counter()
	surface.fill((50, 50, 50))

if mode == MODE_DB:
	def render_base():
		render_default()
else:
	def render_base():
		render_default()
		render_key()

def render_static(t):
	for _ in range(round(t/spf)):
		render_base()
		render_static_pointer(data_rects[index])
		if mode != MODE_DB:
			render_static_pointer(key_rects[keyindex])
		next_frame()
def move_pointer(step, step_format):
	global index
	t = 2#round(.5/spf)
	for i in range(step):
		for j in range(t):
			render_base()
			render_moving_pointer(data_rects[(index+i)%len(data)], data_rects[(index+i+1)%len(data)], j/t, step_format(i))
			if mode != MODE_DB:
				render_static_pointer(key_rects[keyindex])
			next_frame()
	index = (index + step) % len(data)
def move_key_pointer():
	global keyindex
	t = 2#round(.5/spf)
	for i in range(t):
		render_base()
		render_static_pointer(data_rects[index])
		render_moving_pointer(key_rects[keyindex], key_rects[(keyindex+1)%len(key)], i/t, "")
		next_frame()
	keyindex = (keyindex + 1) % len(key)
def output_char():
	global result
	t = round(.5/spf)
	for i in range(t):
		render_base()
		render_static_pointer(data_rects[index])
		if mode != MODE_DB:
			render_static_pointer(key_rects[keyindex])
		render_moving_char(data[index], data_rects[index], result_rects[len(result)], i/t)
		next_frame()
	result += data[index]
def remove_char():
	global data
	moving = data[index+1:]
	data = data[:index]
	t = round(.5/spf)
	for i in range(t):
		render_base()
		render_static_pointer(data_rects[index])
		if mode != MODE_DB:
			render_static_pointer(key_rects[keyindex])
		for j, c in enumerate(moving):
			render_moving_char(c, data_rects[j+len(data)+1], data_rects[j+len(data)], i/t, (255,255,50), 0)
		next_frame()
	data += moving
def unpack_key(skip):
	t1 = round(.75/spf)
	base = key_rects[keyindex]
	targets1 = [(base[0], base[1]-letter_box_offset*(i+1)) for i in range(skip)]
	for i in range(t1):
		render_base()
		render_static_pointer(data_rects[index])
		if mode != MODE_DB:
			render_static_pointer(key_rects[keyindex])
		for x in targets1:
			render_moving_rect(base, x, (i/t1)**.7, letter_box_width+4, (60,60,255))
		next_frame()
	t2 = round(2/spf)
	targets2 = [data_rects[(index+i)%len(data)] for i in range(skip)]
	for i in range(t2):
		render_base()
		render_static_pointer(data_rects[index])
		if mode != MODE_DB:
			render_static_pointer(key_rects[keyindex])
		for x,y in zip(targets1, targets2):
			render_moving_rect(x, y, (i/t2), letter_box_width+4, (60,60,255))
		next_frame()

spf = 0.015
prev = time.perf_counter()
render_static(5)
if mode == MODE_DB:
	while data:
		move_pointer(key, lambda i: str(i+1)+".")
		render_static(.2)
		output_char()
		render_static(.2)
		remove_char()
		render_static(.2)
elif mode == MODE_HCSTSBSH:
	while data:
		unpack_key(ord(key[keyindex])-64)
		move_pointer(ord(key[keyindex])-64, lambda i: chr(i+65))
		render_static(.2)
		move_key_pointer()
		render_static(.2)
		output_char()
		render_static(.2)
		remove_char()
		render_static(.2)
elif mode == MODE_D5:
	while data:
		unpack_key(key[keyindex])
		move_pointer(key[keyindex], lambda i: str(i+1)+".")
		render_static(.2)
		move_key_pointer()
		render_static(.2)
		output_char()
		render_static(.2)
		remove_char()
		render_static(.2)
render_static(5)
