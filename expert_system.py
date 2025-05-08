def get_response(user_input):
    user_input = user_input.lower().strip()
    
    # Greetings
    if user_input in ["hi", "hello", "hey"]:
        return "Hello! I'm your basic medical assistant. How can I help?"
    elif user_input in ["good morning", "morning"]:
        return "Good morning! What symptoms are you experiencing?"
    elif user_input in ["good evening", "evening"]:
        return "Good evening! How can I assist you today?"
    
    # Fever related
    elif "fever" in user_input or "temperature" in user_input:
        if "chills" in user_input:
            return "Fever with chills could indicate infection. Rest and consult a doctor if it persists."
        else:
            return "For fever, rest and drink plenty of fluids. If above 102°F, see a doctor."
    
    # Cough related
    elif "cough" in user_input:
        if "dry" in user_input and "throat" in user_input:
            return "For dry cough and sore throat, try warm salt water gargles and lozenges."
        elif "persistent" in user_input:
            return "Persistent cough needs medical evaluation. Please consult a doctor."
        else:
            return "For cough, drink warm fluids and rest. If it continues, see a doctor."
    
    # Cold/Flu
    elif "cold" in user_input or "flu" in user_input:
        if "runny nose" in user_input or "sneezing" in user_input:
            return "For cold with runny nose, rest and drink fluids. Could be allergies."
        else:
            return "For cold/flu symptoms: rest, fluids, and OTC meds may help."
    
    # Headache
    elif "headache" in user_input or "migraine" in user_input:
        if "nausea" in user_input:
            return "Headache with nausea could be migraine. Rest in dark room and see a doctor."
        else:
            return "For headache, rest in quiet place and hydrate. If frequent, see a neurologist."
    
    # Stomach issues
    elif "stomach" in user_input or "indigestion" in user_input:
        if "vomit" in user_input or "nausea" in user_input:
            return "Nausea/vomiting could be food poisoning. Stay hydrated and see doctor if severe."
        else:
            return "For stomach pain, eat light foods. If persists, see gastroenterologist."
    
    # COVID
    elif "covid" in user_input:
        if "positive" in user_input:
            return "If COVID positive, isolate and monitor oxygen levels. Seek medical help."
        elif "smell" in user_input or "taste" in user_input:
            return "Loss of smell/taste are COVID symptoms. Get tested and isolate."
        else:
            return "COVID symptoms: fever, cough, breathing difficulty. Get tested if concerned."
    
    # Skin issues
    elif "rash" in user_input or "itch" in user_input:
        return "For rashes/itching, avoid scratching. See dermatologist if it spreads."
    elif "pimple" in user_input or "acne" in user_input:
        return "For pimples, maintain hygiene and avoid oily foods. See dermatologist if severe."
    
    # Pain
    elif "body pain" in user_input or "muscle pain" in user_input:
        if "joint" in user_input:
            return "For joint pain, try hot compress. See orthopedist if persists."
        else:
            return "Body/muscle pain may need rest. If with fever, could be infection."
    
    # Goodbyes
    elif user_input in ["bye", "goodbye", "exit", "quit"]:
        return "Goodbye! Take care and feel better soon!"
    elif "thank" in user_input:
        return "You're welcome! Wishing you good health."
    
    # Default response
    else:
        return "I'm a basic medical assistant. Could you describe your symptoms more simply?"

def main():
    print("Medical Chatbot Assistant (Basic Version)")
    print("Type your symptoms or questions. Type 'exit' to end.")
    
    while True:
        user_input = input("You: ")
        if user_input.lower() in ['exit', 'quit', 'bye']:
            print("Bot: Goodbye! Take care.")
            break
        response = get_response(user_input)
        print("Bot:", response)

if __name__ == "__main__":
    main()