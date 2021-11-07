# Wayve - Project documentation

**Team Members:** David Sauer, Azur Mešić, Valeria Chavez-Klier, Michael Giang, Ralf Vetter
**Author:** David Sauer (davidsauer@web.de)

This Git project includes our team outcome during the 2nd Gastrohackathon on the 6th/7th November 2021 at the Messezentrum Salzburg. Within a 24-hours-challenge, we aimed to develop a novel and futuristic concept for tourism in the near future. With Wayve we present a more non-digital approach for drifting throughout the city like never before. Thanks to its unique outlook, tourists can experience more city’s insights without using any digital device other than a screen-less wearable. Moreover, they can meet open-minded locals on their way and interact intuitively with them just by waving. Finally, all these memories would be saved on the phone to access them later and relive the trip in detail once more.



# Important files
- Link
The user flow describes three basic flows of the main interactions. Those are meeting locals, finding points of interest (POI), and accessing previous memories. The first flow deals with finding a POI. The app does not offer specific locations, instead users are limited to broader options such as "bar/cafe", musem, beach, etc. The app then picks at random from one of the nearby avaliable options and activates the bracelet. The bracelet guides the user through vibrations, lights and sound to their destination. There is no other way to find the destination, since the goal is to encourage exploration. The second flow deals with meeting locals. Firstly the option must be enabled inside the app, otherwise the functionality is disabled. If active, no other user input is required. Once the user is close to a friendly local person both of their wristbands will vibrate. Users are encouraged to wave at the other person, and once both wave, a connection is formed and stored in the app. The final flow deals with accessing memories. Here users can see all of their pictures, places they have visited and every person they have met and connected with thus far.

- `xxx.xd`
The xd-file contains the current state of the companion application which is mainly there to revisit collected experiences in retrospect. After building some rough wireframes in the beginning to start prototyping, we quickly passed over to conceptualise the two main user flows in high-fidelity. (Explain flows in more detail; model is iPhone 11, Apple design language, anything else?)

- `wearable.ino`
In this Arduino script we prototyped first simple demos of our two main user interactions with the wearable device. That means
	>**a)** the user interaction when meeting up with a local
	>**b)** the user interaction when connecting with a POI

	More details on how to rebuild the prototype and try out the interaction demos follows in the chapter below.

# Our wearable prototype

The prototype setup is built on the single-board microcontroller **Arduino UNO**. The programming language is C++. In order to rebuild the prototype, we recommend using the Arduino IDE. As you have to install some libraries (see `#includes` in `wearable.ino`) to make the used hardware components work correctly, you can do that easily via the IDE (Tools > Manage libraries).

We added a circuit diagram of the hardware setup in the media folder. Just follow this instruction while building it.

## List of required materials

- asdf
- sdf
- sdf
- sdf

## Necessary tools

- dfasdf
- asdasd
- asdasd

## Using the prototype

You can switch between the two user interaction demos with the button(s) on the small breadboard. A little RGB right next to it visualises in which demo you are in. Pictures and videos of both, the prototype and the user interactions can be visited in the media folder.

>**Turquoise light:**	Interaction demo #1 - Meeting a local
>**Orange light:** 		Interaction demo #2 - Connecting with a POI

### Interaction demo #1 - Meeting a local

The demo starts with a notification that an open-minded local is nearby (blinking light). You think about connect with the local to get to know more about the city you are visiting. Once both decided to look for each other and connect, the bracelette enters a searching mode (rotating light). Awesome, I think you found each other after two minutes of searching. Let's get ready to connect. How do we do that? With a typical gesture that is older than any electrical device you might know - just wave to each other. The bracelette recognizes the gesture and connects with the local (brightening circle). Now let's forget the technical part, put your smartphone away and collect exciting experiences in new cities and countries you won't forget for your whole live. Don't worry, your bracelette remembers the connection and saves a personal token (photo, voice memo, etc.) of your peer to revisit the memory digitally in retrospect.

### Interaction demo #2 - Connecting with a POI

The second demo is about connecting with a POI. A POI can be any local activity (like a sightseeing tour) or building (local bar). The operators can decide to be part of our ecosystem. Once you decided inside the companion app to receive notifications about special kinds of POI's in your surrounding, this function will be available. Assuming you want to visit those special local restaurants, you receive a notification (blinking light). When you entered the restaurant, you can connect to the POI via RFID (filling circle). Let's hope you get a discount on your delicious pizza for that ;-)

# Outlook

add vibration motor, 