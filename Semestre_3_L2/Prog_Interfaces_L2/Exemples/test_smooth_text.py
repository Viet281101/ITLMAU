
import tkinter as tk

def interpolate(color_a, color_b, t):
    # 'color_a' and 'color_b' are RGB tuples
    # 't' is a value between 0.0 and 1.0
    # this is a naive interpolation
    return tuple(int(a + (b - a) * t) for a, b in zip(color_a, color_b))


class Application(tk.Tk):

    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        self.title("Font Color Test")
        self.geometry("256x64")
        self.resizable(width=False, height=False)

        self.label = tk.Label(self, text="Hello World", pady=32)
        self.label.pack()

        # On my system (Windows 7, classic theme) this is "SystemButtonFace"
        label_background_system_color = self.label.cget("background")

        label_background_16_bit_color = self.label.winfo_rgb(label_background_system_color)

        # Again, on my system, this is RGB(212, 208, 200)
        label_background_8_bit_color = tuple(value >> 8 for value in label_background_16_bit_color)

        # This isn't really required. Making a custom label foreground color just to show it doesn't have to be black.
        label_foreground_8_bit_color = tuple((255, 0, 0))

        # I want the the label to "fade in" from the background color to completely red
        self.start_color = label_background_8_bit_color
        self.end_color = label_foreground_8_bit_color

        # Let's say I want a smooth fade in transition at a rate of 60 fps and a duration of 1 second

        self.duration_ms = 1000
        self.frames_per_second = 60
        self.ms_sleep_duration = 1000 // self.frames_per_second
        self.current_step = 0

        self.update_label()


    def update_label(self):

        t = (1.0 / self.frames_per_second) * self.current_step
        self.current_step += 1

        new_color = interpolate(self.start_color, self.end_color, t)
        self.label.configure(foreground="#%02x%02x%02x" % new_color)

        if self.current_step <= self.frames_per_second:
            self.after(self.ms_sleep_duration, self.update_label)


def main():

    application = Application()
    application.mainloop()

    return 0


if __name__ == "__main__":
    import sys
    sys.exit(main())
