import { useEffect, useState } from 'react';

export function FileSelector({ onSelect }) {
  const [programs, setPrograms] = useState([]);
  const [selected, setSelected] = useState('');

  useEffect(() => {
    async function loadPrograms() {
      const files = await window.api.getMiPrograms();
      setPrograms(files);
      if (files.length > 0) {
        setSelected(files[0]);
        onSelect?.(files[0]);
      }
    }

    loadPrograms();
  }, []);

  function handleChange(e) {
    const value = e.target.value;
    setSelected(value);
    onSelect?.(value);
  }

  if (programs.length === 0) {
    return <span>No programs found</span>;
  }

  return (
    <select value={selected} onChange={handleChange} style={{width: "100%", borderRadius: "5px", padding: "3px"}}>
      {programs.map(program => (
        <option key={program} value={program}>
          {program}
        </option>
      ))}
    </select>
  );
}
