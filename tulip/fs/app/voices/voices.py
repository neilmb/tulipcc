# voices.py
# drums.py
# lvgl drum machine for Tulip

import tulip
import midi
import lvgl as lv
import amy
from patches import patches

def redraw(app):
    # draw bg_x stuff, like the piano
    (app.screen_w, app.screen_h) = tulip.screen_size()

    # piano size
    app.piano_w = app.screen_w - 100 # initial, will get adjusted slightly
    app.piano_x = 50 # initial, will get adjusted slightly
    app.piano_h = 250
    app.white_key_w = 50

    # computed
    app.piano_y = app.screen_h - app.piano_h
    app.black_key_w = int(app.white_key_w/2)
    app.black_key_h = int(float(app.piano_h) * (2.0/3.0))
    app.white_keys = int(app.piano_w / app.white_key_w)-1
    app.piano_w = app.white_keys * app.white_key_w # reset
    app.piano_x = int( (app.screen_w - app.piano_w)/2)
    tulip.bg_rect(app.piano_x, app.piano_y, app.piano_w, app.piano_h, 255, 1)
    app.black_idx = [1,2,4,5,6,8,9,11,12,13,15,16,18,19,20,22,23] # etc
    for i in range(app.white_keys)[1:]:
        white_line_x = app.piano_x+(i*app.white_key_w)
        tulip.bg_line(white_line_x, app.piano_y, white_line_x, app.piano_y+app.piano_h, 0)
        if i in app.black_idx:
            tulip.bg_rect(white_line_x-int(app.white_key_w/4), app.piano_y, app.black_key_w, app.black_key_h, 0, 1)

class Settings(tulip.UIElement):
    def __init__(self, width=350, height=300):
        super().__init__()
        self.group.set_size(width, height)
        self.group.remove_flag(lv.obj.FLAG.SCROLLABLE)
        self.label = lv.label(self.group)
        self.label.set_text("sequencer and arpeggiator")
        self.rect = lv.obj(self.group)
        self.rect.set_style_bg_color(tulip.pal_to_lv(9), 0)
        self.rect.remove_flag(lv.obj.FLAG.SCROLLABLE)

        self.rect.set_size(width-25,height-20)
        self.rect.align_to(self.label,lv.ALIGN.OUT_BOTTOM_LEFT,0,0)

        self.tempo = lv.slider(self.rect)
        self.tempo.set_style_bg_opa(lv.OPA.COVER, lv.PART.MAIN)
        self.tempo.set_width(220)
        self.tempo.set_style_bg_color(tulip.pal_to_lv(255), lv.PART.INDICATOR)
        self.tempo.set_style_bg_color(tulip.pal_to_lv(255), lv.PART.MAIN)
        self.tempo.set_style_bg_color(tulip.pal_to_lv(129), lv.PART.KNOB)
        self.tempo.align_to(self.rect, lv.ALIGN.TOP_LEFT,0,0)
        self.tempo_label = lv.label(self.rect)
        self.tempo.set_value(int(tulip.seq_bpm() / 2.4),lv.ANIM.OFF)
        self.tempo_label.set_text("%d BPM" % (tulip.seq_bpm()))
        self.tempo_label.align_to(self.tempo, lv.ALIGN.OUT_RIGHT_MID,10,0)
        self.tempo.add_event_cb(self.tempo_cb, lv.EVENT.VALUE_CHANGED, None)

        alabel = lv.label(self.rect)
        alabel.set_text("Arpeggiator:")
        alabel.align_to(self.tempo, lv.ALIGN.OUT_BOTTOM_LEFT,0,30)
        self.arpegg = lv.switch(self.rect)
        self.arpegg.set_style_border_width(1, lv.PART.MAIN)
        self.arpegg.set_style_border_color(tulip.pal_to_lv(129), 0)
        self.arpegg.align_to(alabel, lv.ALIGN.OUT_RIGHT_MID,10,0)
        self.arpegg.add_event_cb(self.arpegg_cb, lv.EVENT.VALUE_CHANGED, None)
        hlabel = lv.label(self.rect)
        hlabel.set_text("Hold:")
        hlabel.align_to(self.arpegg, lv.ALIGN.OUT_RIGHT_MID,10,0)
        self.hold = lv.switch(self.rect)
        self.hold.set_style_border_width(1, lv.PART.MAIN)
        self.hold.set_style_border_color(tulip.pal_to_lv(129), 0)
        self.hold.align_to(hlabel, lv.ALIGN.OUT_RIGHT_MID,10,0)
        self.hold.add_event_cb(self.hold_cb, lv.EVENT.VALUE_CHANGED, None)

        self.mode = ListColumn("mode", ["Up", "Down", "U&D", "Rand"], width=130, height=160, selected=0)
        self.mode.group.set_parent(self.rect)
        self.mode.group.set_style_bg_color(tulip.pal_to_lv(9),0)
        self.mode.group.align_to(alabel, lv.ALIGN.OUT_BOTTOM_LEFT, 0, 20)
        self.range = ListColumn("range", ["1", "2", "3"], width=130, height=160, selected=0)
        self.range.group.set_parent(self.rect)
        self.range.group.set_style_bg_color(tulip.pal_to_lv(9),0)
        self.range.group.align_to(self.mode.group, lv.ALIGN.OUT_RIGHT_TOP, 10, 0)

    def tempo_cb(self,e):
        new_bpm = self.tempo.get_value()*2.4
        if(new_bpm < 1.0): new_bpm = 1
        tulip.seq_bpm(new_bpm)
        self.tempo_label.set_text("%d BPM" % (tulip.seq_bpm()))
    def hold_cb(self,e):
        if(self.hold.get_state()==3): 
            self.arpegg_hold = True
        else:
            self.arpegg_hold = False
    def arpegg_cb(self,e):
        if(self.arpegg.get_state()==3): 
            self.arpegg_on = True
        else:
            self.arpegg_on = False


class ListColumn(tulip.UIElement):
    def __init__(self, name, items=None, selected=None, width=175, height=300):
        super().__init__() 
        self.name = name
        self.selected = selected
        self.group.set_size(width,height)
        self.group.remove_flag(lv.obj.FLAG.SCROLLABLE)
        self.label = lv.label(self.group)
        self.label.set_text(name)
        self.list = lv.list(self.group)
        self.list.set_size(width-25,height-20)
        self.list.align_to(self.label,lv.ALIGN.OUT_BOTTOM_LEFT,0,0)
        self.buttons = []
        self.button_texts = []
        tulip.lv_depad(self.list)
        tulip.lv_depad(self.group)
        tulip.lv_depad(self.label)
        self.replace_items(items)
        self.default_bg = 36
        if(self.selected is not None):
            self.buttons[self.selected].set_style_bg_color(tulip.pal_to_lv(129), 0)

    def replace_items(self, items):
        if items is not None:
            self.list.clean()
            self.buttons = []
            for i in items:
                button = self.list.add_button(lv.SYMBOL.PLUS, i)
                button.add_event_cb(self.list_cb, lv.EVENT.CLICKED, None)
                self.buttons.append(button)
                self.button_texts.append(i)

    def select(self, index, defer=False):
        if(self.selected is not None):
            self.buttons[self.selected].set_style_bg_color(tulip.pal_to_lv(self.default_bg), 0)
        self.selected = index
        if index is not None:
            self.buttons[self.selected].set_style_bg_color(tulip.pal_to_lv(129), 0)
            if(self.name=='channel'):
                current_patch(self.selected+1)
            elif(self.name=='synth'):
                update_patches(self.button_texts[self.selected])
            else:
                if not defer: update_map()


    def list_cb(self, e):
        button = e.get_target_obj()
        self.select(button.get_index())

def play_note_from_coord(app, x, y):
    white_key = int((x-app.piano_x)/app.white_key_w)
    if(white_key in app.black_idx and y<app.piano_y+app.black_key_h):
        print('black %d' % (white_key))
    else:
        print('white %d' % (white_key))


def touch(up):
    global app
    x,y = [-1,-1,-1], [-1,-1,-1]
    (x[0],y[0],x[1],y[1],x[2],y[2]) = tulip.touch()
    for i in range(3):
        if(x[i] >= app.piano_x and x[i] <= app.piano_x+app.piano_w and y[i] >= app.piano_y and y[i] <= app.piano_y+app.piano_h):
            if(not up):
                play_note_from_coord(app, x[i], y[i])
    #print("got points up %d : %d,%d %d,%d %d,%d" % (up, points[0], points[1], points[2], points[3], points[4], points[5] ))

def process_key(key):
    global app
    # play kb notes from keyboard?
    pass

def step(t):
    global app
    if(app.redraw_ticks is not None):
        app.redraw_ticks = app.redraw_ticks - 1
        if(app.redraw_ticks == 0):
            redraw(app)
            app.redraw_ticks = None

def quit(screen):
    deactivate(app)
    tulip.seq_remove_callback(step)

def activate(screen):
    app.redraw_ticks = 2
    # start listening to the keyboard again
    tulip.keyboard_callback(process_key)
    tulip.touch_callback(touch)

def deactivate(screen):
    # i am being switched away -- keep running but clear and close any active callbacks 
    tulip.bg_clear()
    tulip.keyboard_callback()
    tulip.touch_callback()

# actually make the change in our midi map
def update_map():
    global app
    # channels guaranteed to always be selected
    if(app.patches.selected is not None and app.polyphony.selected is not None and app.synths.selected is not None):
        patch_no = app.patches.selected
        if(app.synths.selected == 1): patch_no += 128
        if(app.synths.selected == 2): patch_no += 256
        if(app.synths.selected == 3): patch_no += 1024
        channel = app.channels.selected + 1
        polyphony = app.polyphony.selected + 1
        # Check if this is a new thing
        if not (midi.patch_map.get(channel, None) == patch_no and midi.polyphony_map.get(channel, None) == polyphony):
            tulip.music_map(channel, patch_number=patch_no, voice_count=polyphony)

# populate the patches dialog from patches,oy
def update_patches(synth):
    global app
    if(synth=='DX7'):
        app.patches.replace_items(patches[128:256])
    if(synth=='Juno-6'):
        app.patches.replace_items(patches[0:128])
    if(synth=='Custom'):
        app.patches.replace_items([("Custom %d" % x) for x in range(32)])
    if(synth=='Misc'):
        app.patches.replace_items([])
    app.patches.label.set_text("%s patches" % (synth))

# Get current settings for a channel from midi.patch_map
def current_patch(channel):
    global app
    if(channel in midi.patch_map):
        p = midi.patch_map[channel]
        if(p<128):
            # We defer here so that setting the UI component doesn't trigger an update before it updates
            app.synths.select(0, defer=True)
            app.patches.select(p, defer=True)
        elif(p>128 and p<256):
            app.synths.select(1, defer=True)
            app.patches.select(p-128, defer=True)
        elif(p<1024):
            app.synths.select(2, defer=True)
            app.patches.select(p-256, defer=True)
        else:
            app.synths.select(3, defer=True)
            app.patches.select(p-1024, defer=True)
        app.polyphony.select(midi.polyphony_map[channel]-1, defer=True)
    else:
        # no patch set for this chanel
        app.patches.select(None)
        app.polyphony.select(None)


def run(screen):
    global app 
    app = screen # we can use the screen obj passed in as a general "store stuff here" class, as well as inspect the UI 
    app.set_bg_color(0)
    app.offset_y = 25
    app.offset_x = 50
    app.redraw_ticks = None
    app.quit_callback = quit
    app.activate_callback = activate
    app.deactivate_callback = deactivate
    tulip.seq_add_callback(step, int(tulip.seq_ppq()/2))

    # Skip 10, drums
    app.channels = ListColumn('channel',["1","2","3","4","5","6","7","8","9","11","12","13","14","15","16"], selected=0, width=100)
    app.add(app.channels, direction=lv.ALIGN.OUT_BOTTOM_LEFT)

    app.synths = ListColumn('synth', ["Juno-6", "DX7", "Misc", "Custom"])
    app.add(app.synths)

    app.patches = ListColumn('patches')
    app.add(app.patches)

    app.polyphony = ListColumn('polyphony', [str(x+1) for x in range(8)], width=100)
    app.add(app.polyphony)

    app.settings = Settings()
    app.add(app.settings)

    current_patch(1)


    app.present()


