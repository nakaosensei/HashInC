import random 

if __name__ == '__main__':
    finalPoint = 10000

    while finalPoint <= 10000000:
        i = 0
        # a = list(range(0,finalPoint))
        a = list()
        for x in range(0, finalPoint):
            a.append(finalPoint*x)
        # random.shuffle(a)
        f = open('./inputs/conflito'+'-'+str(finalPoint)+'.h','w')
        vetor = 'long int size = ' + str(finalPoint) + ";\n";
        vetor += 'TipoElemento vetor[ ] = {'
        while i < finalPoint:
            number = random.randrange(0, 10000)
            vetor += '{.chave = ' + str(a[i])
            vetor += ', .dado = ' + str(number) + '}'
            if i != finalPoint-1:
                vetor += ', '
            i+=1
        vetor += '};'
        f.write(vetor)
        f.close()
        finalPoint *= 10