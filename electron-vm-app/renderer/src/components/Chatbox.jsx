import { useEffect, useRef, useState } from 'react';

export function Chatbox() {
  const [messages, setMessages] = useState([]);
  const [input, setInput] = useState('');
  const messagesEnd = useRef(null);

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
    <div style={{ display: 'flex', flexDirection: 'column', height: '300px', border: '1px solid #ccc', padding: '8px' }}>
      <div style={{ flex: 1, overflowY: 'auto', whiteSpace: 'pre-wrap', fontFamily: 'monospace', marginBottom: '8px' }}>
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
          style={{ width: '100%', boxSizing: 'border-box' }}
          placeholder="Type input for program..."
        />
      </form>
    </div>
  );
}