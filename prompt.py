import pygame,sys

def prompt(x,y,prompt_string,font,screen):
    """Create a prompt for a user to enter a string
    Arguments:
    x -- the x location of the input box to be rendered
    y -- the y location of the input box to be rendered
    prompt_string -- the string to be rendered in the input box
    font -- the font to render the strings with
    screen -- the main screen to render on
    Returns:
    return_string -- a string of what the user entered
    """
    #the value to be returned
    return_string=""
    #calculate the size of the input box, and set it to the 
    width,height = font.size(prompt_string)
    height=height*2+10
    width=width+10
    box = pygame.Rect((x-5, y-5), (width,height))
    #draw the blue box around the input    
    screen.fill((0,0,255),box)
    text = font.render(prompt_string,True,(255,255,255))
    screen.blit(text,(x,y))
    #calculate the white part of the input area
    input_area = pygame.Rect((x, y+height/2-5), (width-10,height/2-5))
    #loop until done(set if enter or escape is hit)
    done=False
    while not done:
        #fill the input area with white
        screen.fill((255,255,255),input_area)
        #put what's currently inputted into the input area
        input_text = font.render(return_string,True,(0,0,0))
        screen.blit(input_text,(x,y+height/2-5))
        pygame.display.flip()
        #wait for an event
        event=pygame.event.wait()
        if event.type == pygame.KEYDOWN:
            #if escape was hit assume the user doesn't want to enter anything, return nothing
            if event.key == pygame.K_ESCAPE:
                done=True
                return_string=""
            #if return was hit, assume the user is finished entering text and return what's been entered
            elif event.key == pygame.K_RETURN:
                done=True
            #if backspace is hit, move the carat back one space and destroy the last letter
            elif event.key == pygame.K_BACKSPACE:
                #make sure there's something in the string first, don't want to kill what's not there
                if len(return_string)>0:
                    return_string=return_string[0:len(return_string)-1]
            else:
                #add the typed letter to the string
                return_string=return_string+event.unicode
    return return_string
 
pygame.init()
size = width, height = 640, 480
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Prompt test")
font=pygame.font.Font("freesansbold.ttf", 12)
frame=0
player_name=""
while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.display.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
                    if event.key==pygame.K_ESCAPE:
                        pygame.display.quit()
                        sys.exit()
                    if event.key==pygame.K_RETURN:
                        player_name=prompt(width/2-100,height/2-64,"Please enter your name:",font,screen)
        screen = pygame.display.get_surface()
    screen.fill((0,0,0))
    text = font.render(player_name,True,(255,255,255))
    screen.blit(text,(0,0))
    pygame.display.flip()
