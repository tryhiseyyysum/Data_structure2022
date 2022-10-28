def build_next(patt):
    """计算next数组"""
    next=[0]
    prefix_len=0    #当前共同前后缀的长度
    i=1
    while i<len(patt):  #从第二个字符开始，依次计算每个字符对应的next值
        if patt[i]==patt[prefix_len]:   #如果字符匹配成功
            prefix_len+=1   #共同前后缀长度加1
            next.append(prefix_len) #将这个长度值加入next数组
            i+=1    #继续比较下一个字符
        else:   #如果字符匹配失败
            if prefix_len==0:   #如果共同前后缀长度为0，说明当前字符之前一个字符都没有匹配成功
                next.append(0)  #那么next[i]就为0
                i+=1        #继续比较下一个字符
            else:
                prefix_len=next[prefix_len-1]   #如果共同前后缀长度不为0，说明当前字符之前有匹配成功的字符
    return next 


def KMP_search(string,patt):
    next=build_next(patt)

    i=0     #主串中的指针
    j=0     #子串中的指针
    while i<len(string):
        if string[i]==patt[j]:  #如果当前字符匹配成功（即S[i] == P[j]），则i++，j++
            i+=1
            j+=1

        elif j>0:   #字符串失配，根据next跳过子串前面的一些字符
            j=next[j-1]
        
        else:       #如果j=0，说明子串的第一个字符都和主串的当前字符不匹配，那么主串的指针后移一位
            i+=1

        if j==len(patt):    #如果j==P.length，说明子串已经匹配完了，返回匹配的起始位置，匹配成功
            return i-j



s="ansdkfsdfrdfserfeajffef"
k="fserfe"

print(KMP_search(s,k))
