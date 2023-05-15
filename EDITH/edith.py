import pyttsx3
import speech_recognition as sr
import datetime as dt
import wikipedia
import webbrowser

engine=pyttsx3.init('sapi5')
voices=engine.getProperty('voices')
print(voices[1].id)
engine.setProperty('voice',voices[1].id)

def speak(audio):
    engine.say(audio)
    engine.runAndWait()

def Wishme():
    speak("Hi, I'm EDITH, your virtual assistant")
    hour=int(dt.datetime.now().hour)
    if hour>=00 and hour<12:
        speak("Good Morning")
    if hour>=12 and hour<18: 
        speak("Good Afternoon")
    elif hour>=18 and hour<=24:
        speak("Good Evening")
    
def takeCommand():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening...")
        r.pause_threshold = 1
        r.energy_threshold = 100
        audio = r.listen(source)
    try:
        print("Recognizing...")
        query=r.recognize_google(audio, language='en-in')
        print("User said ",query)  # print(f"User said: {query}\n")

    except Exception as e:
        print(e)
        print("Say that again please.")
        return "None" 
    return query   

if __name__=="__main__":
    Wishme()
    while True:
        query=takeCommand().lower()
        if 'wikipedia' in query:
            speak("Searching Wikipedia...")
            query=query.replace("wikipedia","")
            results=wikipedia.summary(query,sentences=2)
            speak("According to Wikipedia")
            speak(results)

        elif 'open google':
            webbrowser.open("google.com")

        elif 'open youtube':
            webbrowser.open("youtube.com")

        elif 'open instagram':
            webbrowser.open("https://www.instagram.com/")
        
        elif 'open whatsapp':
            webbrowser.open("https://web.whatsapp.com/")

        elif 'open La Liga':
            webbrowser.open("https://www.google.com/search?q=la+liga&sxsrf=AJOqlzW5EAC3aSSku5W6WBNlnKxd21nA3Q%3A1675601145439&source=hp&ei=-aTfY6qvGM25hwPr-Ao&iflsig=AK50M_UAAAAAY9-zCR3ha5tCO7A0ZhLV1LMPMjWYZy_b&gs_ssp=eJzj4tDP1TewTC-sMGD0Ys9JVMjJTE8EADYDBaM&oq=&gs_lcp=Cgdnd3Mtd2l6EAEYBDIHCCMQ6gIQJzIHCC4Q6gIQJzIHCC4Q6gIQJzIHCC4Q6gIQJzIHCC4Q6gIQJzIHCC4Q6gIQJzIHCC4Q6gIQJzIHCCMQ6gIQJzIHCCMQ6gIQJzIHCCMQ6gIQJ1AAWABgzSRoAXAAeACAAQCIAQCSAQCYAQCwAQo&sclient=gws-wiz")

    