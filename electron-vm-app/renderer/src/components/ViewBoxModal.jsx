import { useEffect, useRef } from 'react';
import './ViewBoxModal.css';

export function ViewBoxModal({ isOpen, onClose, content, fileName }) {
  const viewEnd = useRef(null);

  // Close on Escape key
  useEffect(() => {
    const handleEscape = (e) => {
      if (e.key === 'Escape') onClose();
    };
    
    if (isOpen) {
      document.addEventListener('keydown', handleEscape);
      return () => document.removeEventListener('keydown', handleEscape);
    }
  }, [isOpen, onClose]);

  if (!isOpen) return null;

  return (
    <div className="ModalOverlay" onClick={onClose}>
      <div className="ModalContent" onClick={(e) => e.stopPropagation()}>
        <div className="ModalHeader">
          <h2>Viewing: {fileName}</h2>
          <button className="CloseButton" onClick={onClose}>×</button>
        </div>
        
        <div className="ModalBody">
          <pre>{content ?? 'Loading...'}</pre>
          <div ref={viewEnd} />
        </div>
      </div>
    </div>
  );
}