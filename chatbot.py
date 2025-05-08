import streamlit as st
import nltk
import random
from nltk.chat.util import Chat
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
from nltk import pos_tag
import wikipedia
import re

# Initialize lemmatizer
lemmatizer = WordNetLemmatizer()

def get_factual_answer(query):
    try:
        summary = wikipedia.summary(query, sentences=2)
        return summary
    except Exception:
        return None

# Custom reflections
custom_reflections = {
    "i am": "you are",
    "i was": "you were",
    "i": "you",
    "i'm": "you are",
    "i'd": "you would",
    "i've": "you have",
    "i'll": "you will",
    "my": "your",
    "you are": "I am",
    "you were": "I was",
    "you've": "I have",
    "you'll": "I will",
    "your": "my",
    "yours": "mine",
    "you": "me",
    "me": "you"
}

# Updated chat patterns with flexible matching
patterns = [
    (r'hi|hello|hey|greetings', ['Hello!', 'Hi there!', 'Greetings!']),
    (r'how are you?', ["I'm doing well, thank you!", "I'm great! How about you?"]),
    (r'(.*)your name(.*)', ["I'm ChatBot. Nice to meet you!", "You can call me ChatBot."]),
    (r'(.*)what can you do(.*)', [
        "I can chat with you about various topics like technology, science, weather, and more!",
        "I can answer questions, provide information, or just have a friendly conversation."
    ]),
    (r'(.*)(age|old)(.*)', ["I'm just a program, so I don't have an age!", "I was created recently, so I'm quite young!"]),
    (r'(.*)(weather|temperature)(.*)', [
        "I'm not connected to weather services, but I hope it's nice where you are!",
        "You might want to check a weather app for accurate forecasts."
    ]),
    (r'(.*)(science|technology|tech)(.*)', [
        "Science and technology are fascinating! Did you know the first computer programmer was Ada Lovelace in the 1840s?",
        "Technology is advancing rapidly. AI like me is just one example of recent developments."
    ]),
    # Updated patterns for sports/football/Tell Me Lies (from your image)
    (r'(.*what is sports.*|.*sports.*|.*about sports.*)', [
        "Sport is a form of physical activity or game. Often competitive and organized, sports use, maintain, or improve physical ability and skills.",
        "Sports are typically competitive physical activities that help maintain or improve physical abilities. They can be individual or team-based."
    ]),
    (r'(.*what is football.*|.*football.*|.*about football.*)', [
        "Football is a family of team sports that involve, to varying degrees, kicking a ball to score a goal. Unqualified, the word football generally means the form of football that is the most popular where the word is used.",
        "Football refers to various team sports involving ball kicking. The most popular version depends on your region (like soccer in the US or association football elsewhere)."
    ]),
    (r'(.*tell me lies.*|.*tell mc lies.*|.*about tell me lies.*)', [
        "Tell Me Lies is an American drama television series created by Meaghan Oppenheimer, based on the 2018 novel of the same name by Carola Lovering. The series was released on Hulu on September 7, 2022.",
        "I see you're asking about Tell Me Lies. It's a TV drama based on a novel, premiered on Hulu in 2022."
    ]),
    # Other existing patterns
    (r'(.*)(music|song|band)(.*)', [
        "Music is wonderful! It can affect our moods and emotions.",
        "There are so many genres of music - pop, rock, classical, jazz... What do you like?"
    ]),
    (r'(.*)(movie|film)(.*)', [
        "Movies are a great way to tell stories. Do you prefer action, comedy, or drama?",
        "The first motion picture was made in the late 19th century. How far cinema has come!"
    ]),
    (r'(.*)(book|read|novel)(.*)', [
        "Reading expands the mind. What's the last book you enjoyed?",
        "Books can transport us to different worlds. I'm a fan of classic literature myself."
    ]),
    (r'(.*)(food|eat|cuisine)(.*)', [
        "Food is essential and delicious! Do you like cooking or prefer eating out?",
        "Every culture has its unique cuisine. What's your favorite dish?"
    ]),
    (r'(.*)(travel|vacation|trip)(.*)', [
        "Traveling broadens our horizons. Where was your last vacation?",
        "There are so many beautiful places in the world to visit!"
    ]),
    (r'(.*)(joke|funny)(.*)', [
        "Why don't scientists trust atoms? Because they make up everything!",
        "Why did the scarecrow win an award? Because he was outstanding in his field!"
    ]),
    (r'(.*)(thank you|thanks)(.*)', ["You're welcome!", "No problem!", "Happy to help!"]),
    (r'(.*)(sorry|apologize)(.*)', ["No need to apologize!", "It's alright!", "No worries!"]),
    (r'(.*)(love|like)(.*)', ["That's wonderful to hear!", "Positive emotions are great!"]),
    (r'(.*)(hate|dislike)(.*)', ["I'm sorry to hear that.", "Sometimes we feel that way."]),
    (r'(.*)(help|support)(.*)', ["I'll do my best to help. What do you need?", "How can I assist you?"]),
    (r'(.*)(time|date)(.*)', ["I don't have access to real-time data, but you can check your device's clock!"]),
    (r'(.*)', [
        "I see. Tell me more about that.",
        "Interesting! Can you elaborate?",
        "I understand. What else would you like to discuss?",
        "That's a good point. What's on your mind?"
    ])
]

chatbot = Chat(patterns, custom_reflections)

def generate_response(user_input):
    # Check if user_input matches any specific pattern (excluding catch-all)
    for pattern, responses in patterns[:-1]:  # exclude last (.*)
        if re.fullmatch(pattern, user_input, re.IGNORECASE):
            return random.choice(responses)

    # Try Wikipedia for factual answer
    wiki_answer = get_factual_answer(user_input)
    if wiki_answer:
        return wiki_answer

    # If Wikipedia fails, try catch-all pattern
    response = chatbot.respond(user_input)
    if response:
        return response

    # Final fallback: NLP-based prompt
    tokens = word_tokenize(user_input.lower())
    tagged = pos_tag(tokens)

    nouns = [word for word, pos in tagged if pos.startswith('NN')]
    verbs = [word for word, pos in tagged if pos.startswith('VB')]

    if nouns:
        return f"Tell me more about {random.choice(nouns)}. I'm interested to hear your thoughts."
    elif verbs:
        return f"What makes you think about {random.choice(verbs)}ing? That's quite interesting."
    else:
        return random.choice([
            "That's an interesting perspective. Can you elaborate?",
            "I'd love to hear more about your thoughts on this.",
            "What else would you like to discuss?",
            "That's quite fascinating. Tell me more."
        ])

def main():
    st.title("🤖 Enhanced ChatBot")
    st.write("Welcome! Ask me about sports, football, 'Tell Me Lies', or anything else.")

    if "history" not in st.session_state:
        st.session_state.history = []

    for message in st.session_state.history:
        with st.chat_message(message["role"]):
            st.markdown(message["content"])

    if user_input := st.chat_input("Type your message here..."):
        st.session_state.history.append({"role": "user", "content": user_input})
        with st.chat_message("user"):
            st.markdown(user_input)

        bot_reply = generate_response(user_input)
        st.session_state.history.append({"role": "assistant", "content": bot_reply})
        with st.chat_message("assistant"):
            st.markdown(bot_reply)

if __name__ == "__main__":
    main()