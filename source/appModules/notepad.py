# An example app module.

import appModuleHandler
import tones


class AppModule(appModuleHandler.AppModule):

    def event_gainFocus(self, obj, nextHandler):
        # tones.beep(256, 200)
        print(123)
        pyautogui.hotkey('shift', 'home')
        pyautogui.hotkey('ctrl', 'c')
        text = pyperclip.paste()
        print(text)

        nextHandler()