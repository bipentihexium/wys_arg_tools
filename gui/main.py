"""
Copyright (c) 2022 bipentihexium

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
"""

import builtins
import json
import keyword
import os
import platform
import shutil
import subprocess
import sys
import time
from tkinter import *
from tkinter import filedialog
from tkinter import messagebox
from tkinter import simpledialog
from tkinter import ttk
import traceback
import types

root = Tk()
root.withdraw()

clibpath = "./c_wys_lib.dll" if platform.system() == "Windows" else "./c_wys_lib.so"
if not os.path.exists(clibpath) and os.path.exists("./wys_lib.c"):
	compiler = next((c for c in ["clang","gcc","cc"] if shutil.which(c)), None)
	if compiler and messagebox.askyesno("compile wys_lib.c?", "wys_lib.c was found, but it's dl was not. Do you want to compile it with `" + compiler + "`?"):
		cmd = [compiler, "-Wall", "-Wextra", "-Wpedantic", "-O3", "-march=native", "-fPIC", "-shared", "-o" + clibpath, "./wys_lib.c"]
		if messagebox.askokcancel("compile command", "run `" + " ".join(cmd) + "`?"):
			cp = subprocess.Popen(cmd)
			returncode = cp.wait()
			if returncode:
				messagebox.showerror("compilation failed", "compilation failed with return code " + str(returncode) + ".")
			else:
				messagebox.showinfo("compilation complete", "compilation successful!")

from wys_lib import *
import wys_lib

class AttrSettings(dict):
	def __getattr__(self, attr):
		return self[attr]

with open("settings.json", "r") as f:
	settings = AttrSettings(json.loads(f.read()))
	colors = AttrSettings(settings.colors)

root.deiconify()
root.title("WYS ARG tools GUI :)")
root.config(bg=colors.bg)

menubar = Menu(root, activeborderwidth=0, relief=FLAT, bd=0, bg=colors.menu_bg, fg=colors.menu_fg, activebackground=colors.active_bg)
savemenu = Menu(menubar, activeborderwidth=0, tearoff=0, relief=FLAT, bd=0, bg=colors.menu_bg, fg=colors.menu_fg, activebackground=colors.active_bg)
def run_script_wrapper():
	run_custom_script()
savemenu.add_command(label="Run", command=run_script_wrapper)
status_timestamp = lambda: time.strftime("%H:%M:%S", time.gmtime())
def save_script_as():
	global codefile, codewidget, statuslabel
	f = filedialog.asksaveasfilename(initialdir="./saved/scripts/", defaultextension=".py")
	if not f:
		return
	try:
		codefile = f
		with open(codefile, "w") as f:
			f.write(codewidget.get("1.0", END))
		statuslabel.config(text="[" + status_timestamp() + "] Written script to " + codefile)
		reload_scripts()
	except IOError:
		statuslabel.config(text="[" + status_timestamp() + "] Failed to write script to " + codefile)
	finally:
		if f:
			f.close()
def save_script():
	global codefile, codewidget, statuslabel
	if codefile:
		try:
			with open(codefile, "w") as f:
				f.write(codewidget.get("1.0", END))
			statuslabel.config(text="[" + status_timestamp() + "] Written script to " + codefile)
		except IOError:
			statuslabel.config(text="[" + status_timestamp() + "] Failed to write script to " + codefile)
	else:
		save_script_as()
def new_script():
	global codefile, codewidget
	codefile = ""
	codewidget.delete("1.0", END)
savemenu.add_command(label="Save", command=save_script)
savemenu.add_command(label="Save as", command=save_script_as)
savemenu.add_command(label="New", command=new_script)
menubar.add_cascade(label="Script", menu=savemenu)

statusbar = Frame(root, bg=colors.status_bg)
statuslabel = Label(statusbar, text="[" + status_timestamp() + "] loading...", bg=colors.status_bg, fg=colors.status_fg)
statuslabel.pack(side=LEFT)

ttkstyle = ttk.Style(root)
ttkstyle.theme_use("clam")
ttkstyle.configure("Treeview", background=colors.bg, fieldbackground=colors.bg, foreground=colors.fg, lightcolor=colors.border,
	bordercolor=colors.border, darkcolor=colors.border, borderwidth=0)

keywidget = Entry(root, bg=colors.bg, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg, insertbackground=colors.fg, relief=FLAT)

dataframe = Frame(root, bg=colors.status_bg)
datawidget = Text(dataframe, bg=colors.bg, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg, insertbackground=colors.fg, relief=FLAT, height=10)
datascrollbar = Scrollbar(dataframe, orient=VERTICAL, command=datawidget.yview, activebackground=colors.active_bg, activerelief=FLAT, bg=colors.inactive_bg2,
	elementborderwidth=0, highlightbackground=colors.fg, highlightthickness=0, relief=FLAT, troughcolor=colors.inactive_bg)
datawidget.configure(yscroll=datascrollbar.set)
datascrollbar.pack(fill=Y, side=RIGHT)
datawidget.pack(expand=True, fill=BOTH, padx=(0, 1))

codefile = ""
codeframe = Frame(root, bg=colors.status_bg)
builtin_functions = set([name for name, obj in vars(builtins).items() if isinstance(obj, types.BuiltinFunctionType)])
wys_lib_stuff = set(["wys_lib", *wys_lib.__all__, *["py_"+x for x in wys_lib.__all__[wys_lib.__all__.index("dontbother17_decrypt"):]]])
def highlight(w):
	w.tag_remove("keywords", "1.0", END)
	w.tag_remove("builtins", "1.0", END)
	w.tag_remove("wys_lib", "1.0", END)
	w.tag_remove("datakey", "1.0", END)
	w.tag_remove("numbers", "1.0", END)
	w.tag_remove("strings", "1.0", END)
	w.tag_remove("comments", "1.0", END)
	alltxt = w.get("1.0", END)
	ln = 1
	col = 0
	buff = ""
	buffbegin = "1.0"
	state = 0
	strbound = '"'
	for c in alltxt:
		if state == 1: # in string
			if c == strbound:
				state = 0
				w.tag_add("strings", buffbegin, f"{ln}.{col+1}")
		elif state == 2: # in comment
			if c == '\n':
				state = 0
				w.tag_add("comments", buffbegin, f"{ln}.{col}")
		else:
			if c.isalnum() or c == '_':
				if not buff:
					buffbegin = f"{ln}.{col}"
				buff += c
			elif buff:
				if buff in keyword.kwlist:
					w.tag_add("keywords", buffbegin, f"{ln}.{col}")
				elif buff in builtin_functions:
					w.tag_add("builtins", buffbegin, f"{ln}.{col}")
				elif buff in wys_lib_stuff:
					w.tag_add("wys_lib", buffbegin, f"{ln}.{col}")
				elif buff in ("data", "key"):
					w.tag_add("datakey", buffbegin, f"{ln}.{col}")
				elif buff[0].isdigit():
					w.tag_add("numbers", buffbegin, f"{ln}.{col}")
				buff = ""
			if c == '#':
				buffbegin = f"{ln}.{col}"
				state = 2
			elif c in "'\"":
				buffbegin = f"{ln}.{col}"
				strbound = c
				state = 1
		if c == '\n':
			ln += 1
			col = 0
		else:
			col += 1
	w.tag_config("keywords", foreground=colors.keywords)
	w.tag_config("builtins", foreground=colors.builtinfuncs)
	w.tag_config("wys_lib", foreground=colors.wys_lib_stuff)
	w.tag_config("datakey", foreground=colors.data_and_key)
	w.tag_config("numbers", foreground=colors.numbers)
	w.tag_config("strings", foreground=colors.strings)
	w.tag_config("comments", foreground=colors.comments)
class CodeText(Text):
	def __init__(self, *args, **kwargs):
		Text.__init__(self, *args, **kwargs)
		self._orig = self._w + "_orig"
		self.tk.call("rename", self._w, self._orig)
		self.tk.createcommand(self._w, self._proxy)
	def _proxy(self, *args):
		cmd = (self._orig,) + args
		result = self.tk.call(cmd)
		if args[0] in ("insert", "replace", "delete") or \
			args[0:3] == ("mark", "set", "insert"):
			self.event_generate("<<Change>>", when="tail")
		if args[0] in ("insert", "replace", "delete") or \
			args[0:3] == ("mark", "set", "insert") or \
			args[0:2] == ("xview", "moveto") or \
			args[0:2] == ("xview", "scroll") or \
			args[0:2] == ("yview", "moveto") or \
			args[0:2] == ("yview", "scroll"):
			self.event_generate("<<ViewChange>>", when="tail")
		return result
class TextLineNumbers(Canvas):
	def __init__(self, *args, **kwargs):
		self.fgcol = "black"
		if "fg" in kwargs:
			self.fgcol = kwargs["fg"]
			kwargs.pop("fg")
		if "foreground" in kwargs:
			self.fgcol = kwargs["foreground"]
			kwargs.pop("foreground")
		Canvas.__init__(self, *args, **kwargs)
		self.textwidget = None
	def redraw(self):
		self.delete("all")
		i = self.textwidget.index("@0,0")
		while True:
			dline = self.textwidget.dlineinfo(i)
			if dline is None: break
			y = dline[1]
			linenum = str(i).split(".")[0]
			self.create_text(2,y,anchor="nw", text=linenum, fill=self.fgcol)
			i = self.textwidget.index("%s+1line" % i)
codewidget = CodeText(codeframe, bg=colors.bg, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg, insertbackground=colors.fg, relief=FLAT, wrap=None)
codewidget.bind("<<Change>>", lambda _: highlight(codewidget))
codewidget.bind('<Control-s>', lambda _: save_script())
codewidget.bind('<Control-Shift-S>', lambda _: save_script_as())
codewidget.bind('<F5>', lambda _: run_script_wrapper())
codenumbers = TextLineNumbers(codeframe, width=30, fg=colors.fg, bg=colors.bg, highlightbackground=colors.border, highlightthickness=1)
codewidget.bind('<<ViewChange>>', lambda _: codenumbers.redraw())
codewidget.bind('<Configure>', lambda _: codenumbers.redraw())
codenumbers.textwidget = codewidget
codescrollbar = Scrollbar(codeframe, orient=VERTICAL, command=codewidget.yview, activebackground=colors.active_bg, activerelief=FLAT, bg=colors.inactive_bg2,
	elementborderwidth=0, highlightbackground=colors.fg, highlightthickness=0, relief=FLAT, troughcolor=colors.inactive_bg)
codewidget.configure(yscroll=codescrollbar.set)
codescrollbar.pack(fill=Y, side=RIGHT)
codenumbers.pack(fill=Y, side=LEFT)
codewidget.pack(expand=True, fill=BOTH, padx=(0, 1))

outframe = Frame(root, bg=colors.status_bg)
outwidget = Text(outframe, bg=colors.bg, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg, insertbackground=colors.fg, relief=FLAT, height=10)
outwidget.tag_config("stdout", foreground=colors.stdout)
outwidget.tag_config("stderr", foreground=colors.stderr)
outscrollbar = Scrollbar(outframe, orient=VERTICAL, command=outwidget.yview, activebackground=colors.active_bg, activerelief=FLAT, bg=colors.inactive_bg2,
	elementborderwidth=0, highlightbackground=colors.fg, highlightthickness=0, relief=FLAT, troughcolor=colors.inactive_bg)
outwidget.configure(yscroll=outscrollbar.set)
outscrollbar.pack(fill=Y, side=RIGHT)
outwidget.pack(expand=True, fill=BOTH, padx=(0, 1))

treewidget = ttk.Treeview(root, show="tree")
treescrollbar = Scrollbar(root, orient=VERTICAL, command=treewidget.yview, activebackground=colors.active_bg, activerelief=FLAT, bg=colors.inactive_bg2,
	elementborderwidth=0, highlightbackground=colors.fg, highlightthickness=0, relief=FLAT, troughcolor=colors.inactive_bg)
treewidget.configure(yscroll=treescrollbar.set)
def add_data(parent, x, xdict, xid):
	global counter
	for k, v in x.items():
		if type(v) == str:
			treewidget.insert(parent, END, f"{xid}{counter}", text=k)
			xdict[counter] = v
			counter += 1
		else:
			p = treewidget.insert(parent, END, f"x{xid}{counter}", text=k)
			counter += 1
			add_data(p, v, xdict, xid)
keysdict = { }
with open("./saved/keys.json", "r") as f:
	keys = json.loads(f.read())
counter = 0
add_data(treewidget.insert("", END, "keys", text="keys"), keys, keysdict, 'k')
datadict = { }
with open("./saved/data.json", "r") as f:
	data = json.loads(f.read())
counter = 0
add_data(treewidget.insert("", END, "data", text="data"), data, datadict, 'd')
filetree = { }
def find_scripts(d, t):
	for i in os.listdir(d):
		if os.path.isdir(d + i):
			t[i] = { }
			find_scripts(d + i + "/", t[i])
		elif i.endswith(".py"):
			t[i] = d + i
find_scripts("./saved/scripts/", filetree)
counter = 0
scriptdict = { }
add_data(treewidget.insert("", END, "scripts", text="scripts"), filetree, scriptdict, 's')
def reload_scripts():
	global counter, scriptdict
	treewidget.delete("scripts")
	find_scripts("./saved/scripts/", filetree)
	counter = 0
	scriptdict = { }
	add_data(treewidget.insert("", END, "scripts", text="scripts"), filetree, scriptdict, 's')
def tree_load(e):
	item = treewidget.selection()
	if item and item[0]:
		if item[0][0] == 'd':
			x = item[0][1:]
			if x.isdigit():
				datawidget.delete("1.0", END)
				datawidget.insert(END, datadict[int(x)])
		elif item[0][0] == 'k':
			x = item[0][1:]
			if x.isdigit():
				keywidget.delete(0, END)
				keywidget.insert(END, keysdict[int(x)])
		elif item[0][0] == 's':
			x = item[0][1:]
			if x.isdigit():
				try:
					with open(scriptdict[int(x)], "r") as f:
						codewidget.delete("1.0", END)
						codewidget.insert(END, f.read())
					global codefile
					codefile = scriptdict[int(x)]
				except IOError:
					sys.stderr("Failed to open file " + scriptdict[int(x)] + "\n")
treewidget.bind("<Double-1>", tree_load)

def l1a_checked(func, pyfunc, data, key):
	if not key.isdigit():
		return "invalid key!"
	key = int(key)
	if key > 2000000000:
		return pyfunc(data, int(key))
	else:
		return func(data, int(key))
def l2a_checked(func, data, key):
	if any(c not in "ABCDEFGHIJKLMNOPQRSTUVWXYZ[" for c in key):
		return "invalid key!"
	return func(data, key)
def run_crypt_function_checked(checker, func, *args):
	data = datawidget.get("1.0", END)
	if '\n' in data:
		data = data[:data.rfind('\n')]
	key = keywidget.get().strip()
	outwidget.delete(1.0, END)
	if not data:
		outwidget.insert(END, "data input is empty!")
	elif not key:
		outwidget.insert(END, "key input is empty!")
	else:
		outwidget.insert(END, checker(func, *args, data, key))
def run_data_key_function_checked(func):
	data = datawidget.get("1.0", END)
	if '\n' in data:
		data = data[:data.rfind('\n')]
	key = keywidget.get().strip()
	outwidget.delete(1.0, END)
	if not data:
		outwidget.insert(END, "data input is empty!")
	elif not key:
		outwidget.insert(END, "key input is empty!")
	else:
		outwidget.insert(END, func(data, key))
def run_data_function_checked(f):
	data = datawidget.get("1.0", END)
	if '\n' in data:
		data = data[:data.rfind('\n')]
	outwidget.delete(1.0, END)
	if not data:
		outwidget.insert(END, "data input is empty!")
	else:
		outwidget.insert(END, f(data))
def run_custom_script():
	data = datawidget.get("1.0", END)
	if '\n' in data:
		data = data[:data.rfind('\n')]
	key = keywidget.get().strip()
	outwidget.delete(1.0, END)
	code = codewidget.get("1.0", END)
	if not code.strip():
		outwidget.insert(END, "code is empty!")
		return
	class outwidget_io_stream:
		def __init__(self, tag):
			self.outbuff = ""
			self.tag = tag
		def readline(self):
			return simpledialog.askstring("input", ">")
		def write(self, s):
			self.outbuff += s
			if '\n' in s:
				self.flush()
		def flush(self):
			if self.outbuff:
				prev_end = outwidget.index("end-1c")
				outwidget.insert(END, self.outbuff)
				if self.tag:
					outwidget.tag_add(self.tag, prev_end, "end-2c")
				self.outbuff = ""
	sys.stdin = outwidget_io_stream(None)
	sys.stdout = outwidget_io_stream("stdout")
	sys.stderr = outwidget_io_stream("stderr")
	sys_exit_func = sys.exit
	class SilentError(Exception):
		def __init__(self, rc):
			self.rc = rc
	def exit_override(rc=0):
		raise SilentError(rc)
	sys.exit = exit_override
	local_scope, global_scope = { "data":data, "key":key }, { "data":data, "key":key, "wys_lib":wys_lib }
	for x in wys_lib.__all__:
		global_scope[x] = getattr(wys_lib, x)
	try:
		exec(code, global_scope, local_scope)
	except Exception as e:
		if type(e) == SilentError:
			sys.stdout.write("\nProgram exited with return code " + str(e.rc) + "\n")
		else:
			for ln in traceback.TracebackException.from_exception(e).format():
				sys.stderr.write(ln)
	sys.exit = sys_exit_func
	sys.stdin = sys.__stdin__
	sys.stdout = sys.__stdout__
	sys.stderr = sys.__stderr__
commandframe = Frame(root, bg=colors.status_bg)
run_button = Button(commandframe, text="run",command=run_custom_script,
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
dontbother_decrypt_button = Button(commandframe, text="decrypt with L1 algorithm",command=lambda: run_crypt_function_checked(l1a_checked, dontbother17_decrypt, wys_lib.py_dontbother17_decrypt),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
dontbother_encrypt_button = Button(commandframe, text="encrypt with L1 algorithm", command=lambda: run_crypt_function_checked(l1a_checked, dontbother17_encrypt, wys_lib.py_dontbother17_encrypt),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
hcstsbsh_decrypt_button = Button(commandframe, text="decrypt with L2 algorithm", command=lambda: run_crypt_function_checked(l2a_checked, humanscantsolvethis_decrypt),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
hcstsbsh_encrypt_button = Button(commandframe, text="encrypt with L2 algorithm", command=lambda: run_crypt_function_checked(l2a_checked, humanscantsolvethis_encrypt),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
key_reverse_button = Button(commandframe, text="find keys for L2 algorithm", command=lambda: run_data_key_function_checked(lambda d, k: humanscantsolvethis_keys_from_result(d, k)),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
frequency_button = Button(commandframe, text="character frequency", command=lambda: run_data_function_checked(lambda d: frequency(d)),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
frequency_categories_button = Button(commandframe, text="categorized character frequency", command=lambda: run_data_function_checked(lambda d: frequency_categories(d)),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
mask_data_button = Button(commandframe, text="character mask", command=lambda: run_data_key_function_checked(lambda d, k: mask_data(d, k)),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
min_remove_button = Button(commandframe, text="minimal chars removed before", command=lambda: run_data_key_function_checked(lambda d, k: min_remove(d, k)),
	activebackground=colors.active_bg, background=colors.bg, relief=FLAT, highlightbackground=colors.border, highlightthickness=1, fg=colors.fg)
run_button.pack(fill=X)
dontbother_decrypt_button.pack(fill=X)
dontbother_encrypt_button.pack(fill=X)
hcstsbsh_decrypt_button.pack(fill=X)
hcstsbsh_encrypt_button.pack(fill=X)
key_reverse_button.pack(fill=X)
frequency_button.pack(fill=X)
frequency_categories_button.pack(fill=X)
mask_data_button.pack(fill=X)
min_remove_button.pack(fill=X)

root.config(menu=menubar)
statusbar.pack(fill=X, side=BOTTOM)
treewidget.pack(fill=Y, side=LEFT, padx=(1, 1), pady=(1, 1))
treescrollbar.pack(fill=Y, side=LEFT, padx=(1, 1), pady=(1, 1))
commandframe.pack(fill=Y, side=LEFT, padx=(1, 1), pady=(1, 1))
keywidget.pack(fill=X, padx=(1, 1), pady=(1, 1))
dataframe.pack(fill=X, padx=(1, 1), pady=(1, 1))
outframe.pack(fill=X, side=BOTTOM, padx=(1, 1), pady=(1, 1))
codeframe.pack(expand=True, fill=BOTH, padx=(1, 1), pady=(1, 1))

statuslabel.config(text="[" + status_timestamp() + "] loaded")
root.mainloop()
