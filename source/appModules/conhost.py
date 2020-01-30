# An example app module.

import appModuleHandler
import tones
import pyperclip


class AppModule(appModuleHandler.AppModule):

    def event_gainFocus(self, obj, nextHandler):
        #tones.beep(256, 200)
        pyautogui.hotkey('shift', 'home')
        pyautogui.hotkey('ctrl', 'c')
        text = pyperclip.paste()
        print(text)
        nextHandler()