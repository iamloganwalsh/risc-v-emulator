import { useEffect, useRef, useState, forwardRef, useImperativeHandle } from 'react';
import './Chatbox.css'

export const Chatbox = forwardRef((props, ref) => {
  const [messages, setMessages] = useState([]);
  const [input, setInput] = useState('');
  const messagesEnd = useRef(null);

  // Expose addMessage function via ref
  useImperativeHandle(ref, () => ({
    addMessage: (msg) => {
      setMessages((prev) => [...prev, msg]);
    },
    clearMessages: () => {
      setMessages([]);
    }
  }));

  useEffect(() => {
    const unsubscribeOutput = window.api.onVMOutput((data) => {
      setMessages((prev) => [...prev, data]);
    });

    const unsubscribeExit = window.api.onVMExit((code) => {
      setMessages((prev) => [...prev, `[Process exited with code ${code}]`]);
    });

    // Cleanup listeners when component unmounts
    return () => {
      unsubscribeOutput();
      unsubscribeExit();
    };
  }, []);

  useEffect(() => {
    messagesEnd.current?.scrollIntoView({ behavior: 'smooth' });
  }, [messages]);

  const handleSubmit = (e) => {
    e.preventDefault();
    if (input.trim() === '') return;

    window.api.sendVMInput(input);
    setMessages((prev) => [...prev, `> ${input}`]);
    setInput('');
  };

  return (
    <div className="ChatBox" >
      <div className="MessageDisplay" >
        {messages.map((msg, idx) => (
          <div key={idx}>{msg}</div>
        ))}
        <div ref={messagesEnd} />
      </div>

      <form onSubmit={handleSubmit}>
        <input
          type="text"
          value={input}
          onChange={(e) => setInput(e.target.value)}
          className="ChatBoxInput"
          placeholder="Type input for program..."
        />
      </form>
    </div>
  );
});