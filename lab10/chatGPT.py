# import openai

# openai.api_key = "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"


# response = openai.ChatCompletion.create(
#     model="gpt-3.5-turbo",
#     messages=[
#             {"role": "system", "content": "You are a chatbot"},
#             {"role": "user", "content": "Why should DevOps engineer learn kubernetes?"},
#         ]
# )

# result = ''
# for choice in response.choices:
#     result += choice.message.content

# print(result)

import openai
openai.api_key = "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"
messages = [ {"role": "system", "content": 
              "You are a intelligent assistant."} ]
while True:
    message = input("User : ")
    if message:
        messages.append(
            {"role": "user", "content": message},
        )
        chat = openai.ChatCompletion.create(
            model="gpt-3.5-turbo", messages=messages
        )
    reply = chat.choices[0].message.content
    print(f"ChatGPT: {reply}")
    messages.append({"role": "assistant", "content": reply})