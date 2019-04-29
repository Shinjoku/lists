while True:
    try:
        idx = 0
        string = input()
        ans = ''
        stack = []
        ctrl = False
        temp = ""
        for char in string:
            remove = False
            if char == '[':
                if not ctrl:
                    ctrl = True
                else:
                    stack.append(temp)
                    temp = ""
                    remove = True
            if ctrl:
                if char == ']':
                    ctrl = False
                    stack.append(temp)
                    temp = ""
                elif char != '[':
                    temp += char
                remove = True
            if not remove:
                ans += char
            idx += 1
        ans = ans.replace('[', '').replace(']', '')
        print(temp + ''.join(stack[::-1]) + ans)
    except:
        break